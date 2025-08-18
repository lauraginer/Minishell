/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:05:33 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/18 14:33:14 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_token_pipe(t_ast_node *node, t_ms *ms)
{
	return (execute_pipe(node, ms));
}

static int	handle_token_word(t_ast_node *node, t_ms *ms)
{
	if (is_builtin(node->args[0]))
	{
		if (needs_parent_execution(node->args[0]))
			return (execute_builtin(node, ms));
		else
			return (execute_builtin_with_fork(node, ms));
	}
	else
		return (execute_external_command(&node, &ms, ms->my_env));
}

static int	handle_redirection(t_ast_node *node, t_ms *ms)
{
	if (node->type == TOKEN_REDIR_IN || node->type == TOKEN_REDIR_OUT
		|| node->type == TOKEN_REDIR_APPEND
		|| node->type == TOKEN_REDIR_HEREDOC)
		return (execute_redirection(node, ms));
	else
	{
		ms->exit_status = 1;
		return (ms->exit_status);
	}
}

int	execute_ast(t_ast_node *node, t_ms *ms)
{
	ms->exit_status = 0;
	if (!node || !ms)
	{
		ms->exit_status = 1;
		return (ms->exit_status);
	}
	if (node->type == TOKEN_PIPE)
		return (handle_token_pipe(node, ms));
	else if (node->type == TOKEN_WORD)
		return (handle_token_word(node, ms));
	else
		return (handle_redirection(node, ms));
}
