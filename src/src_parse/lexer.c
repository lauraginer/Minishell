

#include "../../inc/minishell.h"



void	print_tokens(t_ms *ms)
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
	free(ms->tokens);
}

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
				free(ms->tokens);
				free(ms->input);
				ms = init_ms();
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
			free (ms);
			ms = init_ms();
			return (FAILURE);
		}
		else if (is_operator(ms))
			token_operator(ms);
	}
	/*Aquí podría añadir un token tipo EOT(final de tokens)*/
	//print_tokens(ms);// esto hay que borrarlo, es para chequear los tokens
	free (ms->input);
	return (SUCCESS);
}
