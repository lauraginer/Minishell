/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:42:23 by lauragm           #+#    #+#             */
/*   Updated: 2025/07/31 16:34:33 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int execute_redirection(t_ast_node *node, t_ms *ms)
{
	int temp_pipe_fd[2];
	
	ms->exit_status = 0;
	if (node->type == TOKEN_REDIR_IN)
		return (handle_input(node, ms));
	else if (node->type == TOKEN_REDIR_OUT)
		return (handle_output(node, ms));
	else if (node->type == TOKEN_REDIR_APPEND)
		return (handle_append(node, ms));
	else if (node->type == TOKEN_REDIR_HEREDOC)
	{
		if (pipe(temp_pipe_fd) == -1)
		{
			perror("pipe");
			ms->exit_status = 1;
			return(ms->exit_status);
		}
		return (handle_heredoc(node, ms, temp_pipe_fd));
	}
	else
	{
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	return(ms->exit_status);
}

/* Para redirecciones:
1. Abrir archivo (open)
2. Configurar FD con dup2  
3. Ejecutar comando con execute_ast()
4. Cerrar archivo

 NO necesitas fork (diferencia clave con pipes):
Las redirecciones modifican el FD actual
El comando se ejecuta en el mismo proceso
Más simple que los pipes

Conceptos:
entrada <
- open(filename, O_RDONLY)
- dup2(fd, STDIN_FILENO)  // stdin lee del archivo
- Comando lee de stdin normal
salida >
- open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)
- dup2(fd, STDOUT_FILENO)  // stdout escribe al archivo
- O_TRUNC: sobrescribe el archivo
append >>
- open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644)
- dup2(fd, STDOUT_FILENO)
- O_APPEND: añade al final del archivo
heredoc <<
// Conceptos más complejos:
- Crear pipe temporal
- Escribir contenido al pipe
- dup2(pipe[0], STDIN_FILENO)
- Simula entrada desde archivo*/

int handle_input(t_ast_node *node, t_ms *ms)
{
	int fd;
	char *filename;
	
	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ms->exit_status = 1;
		return(ms->exit_status);
	}
	filename = node->right->args[0];
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		ms->exit_status = 1;
		return(ms->exit_status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return(execute_ast(node->left, ms)); //ejecutar el nodo izquierdo cuando se ha aplicado la redireccion
}

int handle_output(t_ast_node *node, t_ms *ms)
{
	int fd;
	char *filename;
	
	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ms->exit_status = 1;
		return(ms->exit_status);
	}
	filename = node->right->args[0];
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		ms->exit_status = 1;
		return(ms->exit_status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return(execute_ast(node->left, ms));
}

int handle_append(t_ast_node *node, t_ms *ms)
{
	int fd;
	char *filename;
	
	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ms->exit_status = 1;
		return(ms->exit_status);
	}
	filename = node->right->args[0];
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		ms->exit_status = 1;
		return(ms->exit_status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return(execute_ast(node->left, ms));
}

int handle_heredoc(t_ast_node *node, t_ms *ms, int pipe_fd[2])
{
	char *delimiter;
	char *line;
	
	delimiter = get_heredoc_delimiter(node, ms);
	if (!delimiter)
		return (ms->exit_status);
	while (1)
	{
		line = readline("> ");
		if (handle_heredoc_signal(line, pipe_fd, ms))
			return (ms->exit_status);
		if (!line || ft_strcmp(line, delimiter) == 0) //si coincide line y delimiter
		{
			if(line)
				free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1); 
		free(line);
	}
	close(pipe_fd[1]); //Cerrar escritura (envía EOF al pipe)
	dup2(pipe_fd[0], STDIN_FILENO); //stdin lee del pipe
	close(pipe_fd[0]); //Cerrar lectura original
	return (execute_ast(node->left, ms));  //ejecutar comando
}
