/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:24:51 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/12 18:31:25 by lginer-m         ###   ########.fr       */
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
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_heredoc_signal(char *line, int pipe_fd[2], t_ms *ms)
{
	if (get_signal == SIGINT)
	{
		get_signal = 0;
		if (line)
			free(line);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		setup_signals();
		ms->exit_status = 130;
		return (130);
	}
	return (0);
}

int	process_heredoc_line(char *line, char *delimiter, int pipe_fd[2])
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
	
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (get_signal == SIGINT)
		{
			if (check_heredoc_signal(line, pipe_fd, ms))
			{
				write(1, "\n", 1);
				return (130);
			}
		}
		if (process_heredoc_line(line, delimiter, pipe_fd))
			break; 
	}
	setup_signals();
	return (0);
}
