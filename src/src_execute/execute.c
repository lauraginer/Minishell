/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:05:33 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/31 16:06:01 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Funcion principal del executor:
int execute_ast(t_ast_node *node, t_ms *ms)
{
	ms->exit_status = 0;
	if(!node || !ms)
	{
		ms->exit_status = 1;
		return(ms->exit_status);
	}
	if(node->type == TOKEN_PIPE)
		return (execute_pipe(node, ms));
	else if(node->type == TOKEN_WORD && is_builtin(node->args[0]))
	{
		if (needs_parent_execution(node->args[0]))
			return (execute_builtin(node, ms)); //SIN FORK
		else
			return (execute_builtin_with_fork(node, ms)); //CON FORK
	}
	else if(node->type == TOKEN_WORD)
		return (execute_external_command(&node, &ms, ms->my_env));
    else if (node->type == TOKEN_REDIR_IN || node->type == TOKEN_REDIR_OUT || 
             node->type == TOKEN_REDIR_APPEND || node->type == TOKEN_REDIR_HEREDOC)
		return(execute_redirection(node, ms));
	else
 	{
		ms->exit_status = 1;
		return(ms->exit_status);
	}
	return(ms->exit_status);
}

/*Para manejar file descriptors y crear procesos con fork():
Esto es el núcleo de la parte de ejecución, además de trabajar un poco con las redirecciones,
donde bbásicamente abrimos un archivo y luego redirigimos (usando dup2) la entrada o salida estándar a ese archivo.
En el caso de here-doc (<<), redirigimos la entrada estándar a un pipe.*/

static void execute_left_child(int *pipe_fd, t_ast_node *pipe_node, t_ms *ms)
{
	dup2(pipe_fd[1], STDOUT_FILENO); //redirige su salida al pipe
	close(pipe_fd[0]);
	close(pipe_fd[1]); // cerrar escritura
	execute_ast(pipe_node->left, ms); //RECURSION
	exit(ms->exit_status);
}

static void execute_right_child(int *pipe_fd, t_ast_node *pipe_node, t_ms *ms)
{
	dup2(pipe_fd[0], STDIN_FILENO); //redirige su entrada desde el pipe
	close(pipe_fd[0]); // cerrar lectura
	close(pipe_fd[1]);
	execute_ast(pipe_node->right, ms);
	exit(ms->exit_status);
}

static int wait_children(pid_t left_pid, pid_t right_pid, t_ms *ms)
{
	int status;
	
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
	ms->exit_status = WEXITSTATUS(status);
	return (ms->exit_status);
}

int execute_pipe(t_ast_node *pipe_node, t_ms *ms)
{
	int pipe_fd[2]; //creacion de un pipe
	pid_t left_pid;
	pid_t right_pid;
	
	ms->exit_status = 0;
	if(pipe(pipe_fd) == -1)
	{
		perror("pipe");
		ms->exit_status = 1;
		exit(ms->exit_status);
	}
	left_pid = fork();
	if (left_pid == 0) //hijo izquierdo: stdout → pipe
		execute_left_child(pipe_fd, pipe_node, ms);
	right_pid = fork();
	if(right_pid == 0) //hijo derecho: stdin ← pipe
		execute_right_child(pipe_fd, pipe_node, ms);
	//PROCESO PADRE: cerrar pipes y esperar hijos
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return(wait_children(left_pid, right_pid, ms));
}