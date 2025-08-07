/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:24:51 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/06 22:45:52 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	check_heredoc_signal(char *line, int pipe_fd[2], t_ms *ms)
{
	if (get_signal == SIGINT)
	{
		get_signal = 0;
		if (line)
			free(line);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		restore_signals();
		ms->exit_status = 130;
		return (130);
	}
	return (0);
}

static int	process_heredoc_line(char *line, char *delimiter, int pipe_fd[2])
{
	if (!line)
	{
		printf("minishell: warning: here-document delimited by end-of-file (wanted '%s')\n", delimiter);
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
	free(line);
	return (0);
}

int read_heredoc_lines(char *delimiter, int pipe_fd[2], t_ms *ms)
{
	char *line;
	
	// Configurar señales específicas para heredoc (sin SA_RESTART)
	setup_heredoc_signals();
	while (1)
	{
		// Verificar si llegó SIGINT antes de readline
		if (check_heredoc_signal(NULL, pipe_fd, ms))
			return (130);
		// Leer línea del usuario con prompt ">"
		line = readline("> ");
		// Verificar si llegó SIGINT durante o después de readline
		if (check_heredoc_signal(line, pipe_fd, ms))
		{
			write(1, "\n", 1); // Nueva línea después de ^C
			return (130);
		}
		// Procesar línea: EOF, delimitador o escribir al pipe
		if (process_heredoc_line(line, delimiter, pipe_fd))
			break; // Salir si encontró delimitador o EOF
	}
	// Restaurar configuración normal de señales
	restore_signals();
	return (0);
}
