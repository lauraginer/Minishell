/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:26:48 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/06/20 17:28:07 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//AÑADIR A .h: It checks if the char is a redirection or a pipe,
// and return 1 in that case
int	is_operator(t_parse *parse)
{
	if (parse->input[parse->count] == '<'
		|| parse->input[parse->count] == '>'
		|| parse->input[parse->count] == '|')
		return (1);
	return (0);
}

//AÑADIR A .h: It checks if the char is not allowed, and return 1 in that case
int	is_not_allowed(t_parse *parse)
{
	if (parse->input[parse->count] == '&'
		|| parse->input[parse->count] == ';'
		|| parse->input[parse->count] == '\\')
		return (1);
	return (0);
}
//AÑADIR A .h:It tokenizer input redir (<, <<)
void	token_redir_in(t_list *my_env, t_parse *parse, int j)
{
	parse->input++;
	if (parse->input[parse->count] == '<')
	{
		parse->count++;
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_HEREDOC, j);
	}
	else
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_IN, j);
}
//AÑADIR A .h:It tokenizer output redir (>, >>)
void	token_redir_out(t_list *my_env, t_parse *parse, int j)
{
	parse->input++;
	if (parse->input[parse->count] == '>')
	{
		parse->count++;
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_APPEND, j);
	}
	else
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_OUT, j);
}
