/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:43:09 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/06/19 13:01:47 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	fill_and_add_token_node(t_parse *parse, t_list *my_env, t_token_type type, int j)
{
	t_token	*node;
	char	*value;

	value = ft_substr(parse->input, j, parse->count - j);
	if(!value)
	{
		free_env_list(my_env);
		free_parse(parse);
	}
	node = lstnew_token(value, type);
	if (!node)
	{
		free(value);
		free_env_list(my_env);
		free_parse(parse);
	}
	lstadd_back_token(&(parse->tokens), node);
	return (SUCCESS);
}

int	quot_filt(t_parse *parse, t_list *my_env, char c, t_token_type type)
{
	int		j;

	parse->count++;
	j = parse->count;
	while (parse->input[parse->count] != c && parse->input[parse->count] != '\0')
		parse->count++;
	if (parse->input[parse->count] == '\0')
	{
		printf("Syntax error: quotes unclosed");
		return (FAILURE);
	}
	else
		fill_and_add_token_node(parse, my_env, type, j);
	return (SUCCESS);
}

int lexer(t_list *my_env, t_parse *parse)
{
	while (parse->input[parse->count])
	{
		while (ft_is_space(parse->input[parse->count]))
			parse->count++;
		if (parse->input[parse->count] == '\"')
		{
			if (quot_filt(parse, my_env, '\"', TOKEN_WORD) == FAILURE)
				return (FAILURE);
		}
		else if (parse->input[parse->count] == '\'')
		{
			if (quot_filt(parse, my_env, '\'', TOKEN_S_QUOTES) == FAILURE)
				return (FAILURE);
		}
		parse->count++;
	}
	return (SUCCESS);
}
