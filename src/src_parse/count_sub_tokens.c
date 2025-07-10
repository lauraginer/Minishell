
#include "../../inc/minishell.h"

void	count_dolar_subtokens(t_ms *ms, t_token *aux_t, int *count, char c)
{
	ms->i++;
	if (aux_t->value[ms->i] == '$' || aux_t->value[ms->i] == '0'
		|| aux_t->value[ms->i] == '#' || aux_t->value[ms->i] == '-')
	{
		(*count)++;
		ms->i++;
	}
	else if (aux_t->value[ms->i] == '?')
	{
		(*count)++;
		ms->i++;
	}
	else if (ft_is_space(aux_t->value[ms->i]) || aux_t->value[ms->i] == c
		|| !ft_isalnum(aux_t->value[ms->i]))
		(*count)++;
	else
	{
		while (ft_isalnum(aux_t->value[ms->i]) || aux_t->value[ms->i] == '_')
			ms->i++;
		(*count)++;
	}
}

void	count_subtokens(t_ms *ms, t_token *aux_t, int *count)
{
	int	pos;

	ms->i = 0;
	while (aux_t->value[ms->i])
	{
		pos = ms->i;
		while (aux_t->value[ms->i] && !is_exp_token(aux_t->value[ms->i]))
			ms->i++;
		if (pos != ms->i)
			(*count)++;
		if (aux_t->value[ms->i] == '\'')
		{
			ms->i++;
			while (aux_t->value[ms->i] != '\'')
				ms->i++;
			(*count)++;
			ms->i++;
		}
		count_subtokens2(ms, aux_t, count);
	}
}

void	count_subtokens2(t_ms *ms, t_token *aux_t, int *count)
{
	if (aux_t->value[ms->i] == '\"')
	{
		ms->i++;
		if (aux_t->value[ms->i] == '\"')
		{
			(*count)++;
			ms->i++;
			return ;
		}
		while (aux_t->value[ms->i] != '\"' && aux_t->value[ms->i])
		{
			while (aux_t->value[ms->i] != '\"' && aux_t->value[ms->i] != '$'
				&& aux_t->value[ms->i])
				ms->i++;
			(*count)++;
			if (aux_t->value[ms->i] == '$')
				count_dolar_subtokens(ms, aux_t, count, '\"');
		}
		if (aux_t->value[ms->i] == '\"')
			ms->i++;
	}
	if (aux_t->value[ms->i] == '$')
		count_dolar_subtokens(ms, aux_t, count, '\0');
}
