/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:43:09 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/06/20 17:27:46 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quot_filt(t_parse *parse, t_list *my_env, char c, t_token_type type)
{
	int		j;

	parse->count++;
	j = parse->count;
	while (parse->input[parse->count] != c
		&& parse->input[parse->count] != '\0')
		parse->count++;
	if (parse->input[parse->count] == '\0')
	{
		printf("Syntax error: quotes unclosed");
		return (FAILURE);
	}
	else
	{
		fill_and_add_token_node(parse, my_env, type, j);
		parse->count++;
	}
	return (SUCCESS);
}

//AÑADIR A .h: It tokenizes operators (<, >, <<, >>, |)
void	token_operator(t_list *my_env, t_parse *parse)
{
	int	j;

	j = parse->count;
	if (parse->input[parse->count] == '<')
		token_redir_in(my_env, parse, j);
	else if (parse->input[parse->count] == '>')
		token_redir_out(my_env, parse, j);
	else
	{
		parse->count++;
		fill_and_add_token_node(parse, my_env, TOKEN_PIPE, j);
	}
}

//AÑADIR A .h: It tokenizes everything except quotes
int	token_not_quot(t_list *my_env, t_parse *parse)
{
	int	j;

	j = parse->count;
	while (parse->input[parse->count] && !is_operator(parse)
		&& parse->input[parse->count] != '\"'
		&& parse->input[parse->count] != '\'')
	{
		if (ft_is_space(parse->input[parse->count]))
			break ;
		if (is_not_allowed(parse))
		{
			free (parse);
			parse = init_parse();
			return (FAILURE);
		}
		parse->count++;
	}
	if (j != parse->count)
		fill_and_add_token_node(parse, my_env, TOKEN_WORD, j);
	if (is_operator(parse))
		token_operator(my_env, parse);
	return (SUCCESS);
}

int	lexer(t_list *my_env, t_parse *parse)
{
	while (parse->input[parse->count])
	{
		while (ft_is_space(parse->input[parse->count]))
			parse->count++;
		if (token_not_quot(my_env, parse) == FAILURE)
			return (FAILURE);
		else if (parse->input[parse->count] == '\"')
		{
			if (quot_filt(parse, my_env, '\"', TOKEN_WORD) == FAILURE)
				return (FAILURE);
		}
		else if (parse->input[parse->count] == '\'')
		{
			if (quot_filt(parse, my_env, '\'', TOKEN_S_QUOTES) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}
