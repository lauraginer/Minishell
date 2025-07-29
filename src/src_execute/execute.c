/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:05:33 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/29 20:00:46 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Funcion principal del executor:

int main_execute(t_node node)
{
	if(node->type == TOKEN_PIPE)
		return (execute_pipe(node, ms));
	else if (is_builtin(node->args[0]))
        return execute_builtin(node, ms);
 	else
   		return (execute_external_command(node, ms, STDIN, STDOUT));
}

/*Para manejar file descriptors y crear procesos con fork():
Esto es el núcleo de la parte de ejecución, además de trabajar un poco con las redirecciones,
donde bbásicamente abrimos un archivo y luego redirigimos (usando dup2) la entrada o salida estándar a ese archivo.
En el caso de here-doc (<<), redirigimos la entrada estándar a un pipe.*/
int execute_pipe(t_ast_node *pipe_node, t_ms *ms)
{
	int pipe;
	int pipe_2;
	int pipe_fd[2]; //creacion de un pipe
	int i;
	
	i = 0;
	ms->exit_status = 1;
	if(pipe(pipe_fd) == -1)
	{
		perror("pipe");
		ms->exit_status = 0;
		exit(ms->exit_status);
	}
		
	left_pid = fork();
	if (pid == 0) // estamos en el hijo izquierdo
	{
	// hacer lo necesario
	close(pipe_fds[0]); // según corresponda
	close(pipe_fds[1]); // según corresponda
	}
	else if(pid > 0)// estamos de nuevo en el padre
	{
		// hacer lo mismo para el hijo derecho
		// asegurarse de cerrar también los pipe_fds en el padre
	}
}
    // Crear pipe
    // Fork para comando izquierdo
    // Fork para comando derecho
    // Conectar stdout del izquierdo con stdin del derecho
    // Esperar a ambos procesos

/*Luego tienes que modificar el execute external commands para que integre los pipes
 	// Si input_fd != STDIN, hacer dup2
    // Si output_fd != STDOUT, hacer dup2
    // Ejecutar comando*/