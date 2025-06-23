/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:26:48 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/06/23 12:31:05 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_operator(t_parse *parse)
{
	if (parse->input[parse->i] == '<'
		|| parse->input[parse->i] == '>'
		|| parse->input[parse->i] == '|')
		return (1);
	return (0);
}

int	is_not_allowed(t_parse *parse)
{
	if (parse->input[parse->i] == '&'
		|| parse->input[parse->i] == ';'
		|| parse->input[parse->i] == '\\')
		return (1);
	return (0);
}

void	token_redir_in(t_list *my_env, t_parse *parse, int j)
{
	parse->i++;
	if (parse->input[parse->i] == '<')
	{
		parse->i++;
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_HEREDOC, j);
	}
	else
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_IN, j);
}

void	token_redir_out(t_list *my_env, t_parse *parse, int j)
{
	parse->i++;
	if (parse->input[parse->i] == '>')
	{
		parse->i++;
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_APPEND, j);
	}
	else
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_OUT, j);
}
