/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:58:00 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/13 11:37:31 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_heredoc_pipe(char *delimiter, t_ms *ms)
{
	int	pipe_fd[2];
	int	result;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		ms->exit_status = 1;
		return (-1);
	}
	result = read_heredoc_lines(delimiter, pipe_fd, ms);
	if (result == 130)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static int	validate_heredoc_node(t_ast_node *node, t_ms *ms)
{
	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ms->exit_status = 1;
		return (1);
	}
	return (0);
}

static int	transform_heredoc_node(t_ast_node *node, int heredoc_fd, t_ms *ms)
{
	char	*fd_str;

	fd_str = ft_itoa(heredoc_fd);
	if (!fd_str)
	{
		close(heredoc_fd);
		ms->exit_status = 1;
		return (1);
	}
	node->type = TOKEN_REDIR_IN;
	free(node->right->args[0]);
	node->right->args[0] = fd_str;
	return (0);
}

int	process_heredocs(t_ast_node *node, t_ms *ms)
{
	int	heredoc_fd;

	if (!node)
		return (0);
	ms->exit_status = 0;
	if (process_heredocs(node->left, ms) != 0)
		return (ms->exit_status);
	if (process_heredocs(node->right, ms) != 0)
		return (ms->exit_status);
	if (node->type == TOKEN_REDIR_HEREDOC)
	{
		if (validate_heredoc_node(node, ms) != 0)
			return (1);
		heredoc_fd = create_heredoc_pipe(node->right->args[0], ms);
		if (heredoc_fd == -1)
			return (ms->exit_status);
		if (transform_heredoc_node(node, heredoc_fd, ms) != 0)
			return (1);
	}
	return (ms->exit_status);
}
