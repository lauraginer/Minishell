/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:42:23 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/13 11:32:12 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_redirection(t_ast_node *node, t_ms *ms)
{
	ms->exit_status = 0;
	if (node->type == TOKEN_REDIR_IN)
		return (handle_input(node, ms));
	else if (node->type == TOKEN_REDIR_OUT)
		return (handle_output(node, ms));
	else if (node->type == TOKEN_REDIR_APPEND)
		return (handle_append(node, ms));
	else if (node->type == TOKEN_REDIR_HEREDOC)
	{
		printf("Error: heredoc not preprocessed\n");
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	else
	{
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	return (ms->exit_status);
}

int	handle_input(t_ast_node *node, t_ms *ms)
{
	int		fd;
	char	*filename;
	int		saved_fd;
	int		result;

	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	filename = node->right->args[0];
	fd = get_input_fd(filename, ms);
	if (fd == -1)
		return (ms->exit_status);
	saved_fd = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	if (!is_string_numeric(filename))
		close(fd);
	result = execute_ast(node->left, ms);
	dup2(saved_fd, STDIN_FILENO);
	close(saved_fd);
	return (result);
}

int	handle_output(t_ast_node *node, t_ms *ms)
{
	int		fd;
	char	*filename;
	int		saved_fd;
	int		result;

	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	filename = node->right->args[0];
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	saved_fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	result = execute_ast(node->left, ms);
	dup2(saved_fd, STDOUT_FILENO);
	return (result);
}

int	handle_append(t_ast_node *node, t_ms *ms)
{
	int		fd;
	char	*filename;
	int		result;
	int		saved_fd;

	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	filename = node->right->args[0];
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	saved_fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	result = execute_ast(node->left, ms);
	dup2(saved_fd, STDOUT_FILENO);
	return (result);
}
