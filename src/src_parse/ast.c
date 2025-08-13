/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:27:16 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/08/13 11:27:22 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast_node	*ast_cmd(t_ms *ms, t_token *token)
{
	t_token		*tmp;
	t_ast_node	*new_node;
	int			arg_count;

	arg_count = argument_counter(token);
	if (arg_count > 0)
	{
		new_node = new_ast_node(TOKEN_WORD, ms);
		new_node->args = malloc(sizeof(char *) * (arg_count + 1));
		arg_count = 0;
		tmp = token;
		while (tmp && tmp->type != TOKEN_PIPE)
		{
			if (is_redir(tmp))
				tmp = tmp->next;
			else
				new_node->args[arg_count++] = ft_strdup(tmp->value);
			tmp = tmp->next;
		}
		new_node->args[arg_count] = NULL;
		return (new_node);
	}
	return (NULL);
}

t_ast_node	*ast_file(t_ms *ms, t_token *token)
{
	t_ast_node	*new_node;

	new_node = new_ast_node(TOKEN_WORD, ms);
	new_node->args = malloc(sizeof(char *) * 2);
	if (!new_node->args)
		free_ms(ms);
	new_node->args[0] = ft_strdup(token->value);
	new_node->args[1] = NULL;
	return (new_node);
}

t_ast_node	*ast_redirection(t_ms *ms, t_token *token)
{
	t_token		*tmp;
	t_ast_node	*new_node;
	int			redir_cnt;

	ms->redir_f++;
	redir_cnt = 0;
	tmp = token;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			redir_cnt++;
			if (redir_cnt == ms->redir_f)
			{
				new_node = new_ast_node(tmp->type, ms);
				new_node->left = ast_redirection(ms, token);
				new_node->right = ast_file(ms, tmp->next);
				return (new_node);
			}
		}
		tmp = tmp->next;
	}
	return (ast_cmd(ms, token));
}

t_ast_node	*ast_pipe(t_ms *ms, t_token *token)
{
	t_token		*tmp;
	t_ast_node	*new_node;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			new_node = new_ast_node(tmp->type, ms);
			new_node->left = ast_redirection(ms, token);
			ms->redir_f = 0;
			new_node->right = ast_pipe(ms, tmp->next);
			return (new_node);
		}
		tmp = tmp->next;
	}
	return (ast_redirection(ms, token));
}

t_ast_node	*ast_main(t_ms *ms, t_token *token)
{
	t_ast_node	*new_node;

	new_node = ast_pipe(ms, token);
	free_token_list(ms->tokens);
	return (new_node);
}
