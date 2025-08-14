/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:29:20 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/08/13 14:04:43 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*void	print_tokens(t_ms *ms)
{
	t_token	*curr;

	const char *token_to_str[] = {"TOKEN_WORD",
		"TOKEN_PIPE", "TOKEN_REDIR_IN","TOKEN_REDIR_OUT",
		"TOKEN_REDIR_APPEND", "TOKEN_REDIR_HEREDOC"};
	curr = ms->tokens;
	while (curr)
	{
		printf("TOKEN TYPE: %s\n", token_to_str[curr->type]);
		printf("VALUE: %s\n\n", curr->value);
		curr = curr->next;
	}
	//free_token_list(ms->tokens);
}*/

void	token_operator(t_ms *ms)
{
	int	j;

	j = ms->i;
	if (ms->input[ms->i] == '<')
		token_redir_in(ms, j);
	else if (ms->input[ms->i] == '>')
		token_redir_out(ms, j);
	else
	{
		ms->i++;
		fill_and_add_token_node(ms, TOKEN_PIPE, j);
	}
}

int	token_word(t_ms *ms, int j)
{
	while (ms->input[ms->i] && !is_operator(ms)
		&& !ft_is_space(ms->input[ms->i]) && !is_not_allowed(ms))
	{
		if (ms->input[ms->i] == '\"' || ms->input[ms->i] == '\'')
		{
			ms->quot = ms->input[ms->i];
			ms->i++;
			while (ms->input[ms->i] != ms->quot && ms->input[ms->i])
				ms->i++;
			if (ms->input[ms->i] == '\0')
			{
				printf("Syntax error: quotes unclosed\n");
				free_token_list(ms->tokens);
				free(ms->input);
				init_ms(ms);
				return (FAILURE);
			}
		}
		ms->i++;
	}
	if (j != ms->i)
		fill_and_add_token_node(ms, TOKEN_WORD, j);
	return (SUCCESS);
}

int	lexer(t_ms *ms)
{
	int	j;

	while (ms->input[ms->i])
	{
		while (ft_is_space(ms->input[ms->i]))
			ms->i++;
		j = ms->i;
		if (token_word(ms, j) == FAILURE)
			return (FAILURE);
		else if (is_not_allowed(ms))
		{
			printf("Syntax error: character not supported.\n");
			free (ms->input);
			init_ms(ms);
			return (FAILURE);
		}
		else if (is_operator(ms))
			token_operator(ms);
	}
	free (ms->input);
	return (SUCCESS);
}
/*
	To display the tokens obtained (to check it), include before free(ms->input):
	print_tokens(ms);
*/