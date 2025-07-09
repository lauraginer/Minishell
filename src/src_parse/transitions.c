
#include "../../inc/minishell.h"


int	transit_0(t_token *aux_t, t_state *st)
{
	if (aux_t->type == TOKEN_WORD)
		*st = S1;
	else if (is_redir(aux_t))
		*st = S2;
	else if (aux_t->type == TOKEN_PIPE)
	{
		*st = S4;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	transit_1_2(t_token *aux_t, t_state *st)
{
	if (*st == S1)
	{
		if (aux_t->type == TOKEN_WORD)
			*st = S1;
		else if (is_redir(aux_t))
			*st = S2;
		else if (aux_t->type == TOKEN_PIPE)
			*st = S4;
	}
	else
	{
		if (aux_t->type == TOKEN_WORD)
			*st = S3;
		else if (is_redir(aux_t))
		{
			*st = S2;
			return (FAILURE);
		}
		else if (aux_t->type == TOKEN_PIPE)
		{
			*st = S4;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	transit_3_4(t_token *aux_t, t_state *st)
{
	if (*st == S3)
	{
		if (aux_t->type == TOKEN_WORD)
			*st = S1;
		else if (is_redir(aux_t))
			*st = S2;
		else if (aux_t->type == TOKEN_PIPE)
			*st = S4;
	}
	else
	{
		if (aux_t->type == TOKEN_WORD)
			*st = S1;
		else if (is_redir(aux_t))
			*st = S2;
		else if (aux_t->type == TOKEN_PIPE)
		{
			*st = S4;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
