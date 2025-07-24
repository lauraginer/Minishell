
#include "../../inc/minishell.h"

int	is_redir(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND
		|| token->type == TOKEN_REDIR_HEREDOC)
		return (1);
	return (0);
}

int	syntax_checker(t_ms *ms)
{
	t_token	*aux_t;
	t_state	*st;

	aux_t = ms->tokens;
	st = malloc(sizeof(t_state));
	if (!st)
		free_ms(ms);
	*st = S0;
	while (aux_t)
	{
		if (syntax_checker2(aux_t, st) == FAILURE)
			break ;
		aux_t = aux_t->next;
	}
	if (*st == S2 || *st == S4)
	{
		printf("Syntax error\n");
		free_token_list(ms->tokens);
		free(st);
		init_ms(ms);
		return (FAILURE);
	}
	free(st);
	return (SUCCESS);
}

int	syntax_checker2(t_token *aux_t, t_state *st)
{
	if (*st == S0)
	{
		if (transit_0(aux_t, st) == FAILURE)
			return (FAILURE);
	}
	else if (*st == S1 || *st == S2)
	{
		if (transit_1_2(aux_t, st) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (transit_3_4(aux_t, st) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
