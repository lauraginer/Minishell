/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:43:09 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/06/23 17:07:03 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_parse *parse)
{
	t_token	*curr;

	const char *token_to_str[] = {"TOKEN_WORD",
		"TOKEN_PIPE", "TOKEN_REDIR_IN","TOKEN_REDIR_OUT",
		"TOKEN_REDIR_APPEND", "TOKEN_REDIR_HEREDOC"};
	curr = parse->tokens;
	while (curr)
	{
		printf("TOKEN TYPE: %s\n", token_to_str[curr->type]);
		printf("VALUE: %s\n\n", curr->value);
		curr = curr->next;
	}
	free(parse);
	parse = init_parse();
}

void	token_operator(t_list *my_env, t_parse *parse)
{
	int	j;

	j = parse->i;
	if (parse->input[parse->i] == '<')
		token_redir_in(my_env, parse, j);
	else if (parse->input[parse->i] == '>')
		token_redir_out(my_env, parse, j);
	else
	{
		parse->i++;
		fill_and_add_token_node(parse, my_env, TOKEN_PIPE, j);
	}
}

int	token_word(t_list *my_env, t_parse *parse, int j)
{
	while (parse->input[parse->i] && !is_operator(parse)
		&& !ft_is_space(parse->input[parse->i]) && !is_not_allowed(parse))
	{
		if (parse->input[parse->i] == '\"' || parse->input[parse->i] == '\'')
		{
			parse->quot = parse->input[parse->i];
			parse->i++;
			while (parse->input[parse->i] != parse->quot
				&& parse->input[parse->i])
				parse->i++;
			if (parse->input[parse->i] == '\0')
			{
				printf("Syntax error: quotes unclosed\n");
				free(parse);
				parse = init_parse();
				return (FAILURE);
			}
		}
		parse->i++;
	}
	if (j != parse->i)
		fill_and_add_token_node(parse, my_env, TOKEN_WORD, j);
	return (SUCCESS);
}

int	lexer(t_list *my_env, t_parse *parse)
{
	int	j;

	while (parse->input[parse->i])
	{
		while (ft_is_space(parse->input[parse->i]))
			parse->i++;
		j = parse->i;
		if (token_word(my_env, parse, j) == FAILURE)
			return (FAILURE);
		else if (is_not_allowed(parse))
		{
			printf("Syntax error: character not supported.\n");
			free (parse);
			parse = init_parse();
			return (FAILURE);
		}
		else if (is_operator(parse))
			token_operator(my_env, parse);
	}
	print_tokens(parse);
	return (SUCCESS);
}
