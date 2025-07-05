

#include "../../inc/minishell.h"

void	split_squot_subt(t_ms *ms, t_token *aux_t, int *count)
{
	int	pos;

	ms->i++;
	pos = ms->i;
	while (aux_t->value[ms->i] != '\'')
		ms->i++;
	ms->sub_tokens[*count] = ft_substr(aux_t->value,
			pos, ms->i - pos);
	if (!ms->sub_tokens[*count])
		free_ms(ms);
	(*count)++;
	ms->i++;
}

void	split_norm_subt(t_ms *ms, t_token *aux_t, int *count)
{
	int	pos;

	pos = ms->i;
	while (aux_t->value[ms->i] && !is_exp_token(aux_t->value[ms->i]))
		ms->i++;
	if (pos != ms->i)
	{
		ms->sub_tokens[*count] = ft_substr(aux_t->value, pos, ms->i - pos);
		if (!ms->sub_tokens[*count])
			free_ms(ms);
		(*count)++;
	}
}

void	split_dquot_subt(t_ms *ms, t_token *aux_t, int *count)
{
	if (aux_t->value[ms->i] == '\"')
	{
		ms->i++;
		if (aux_t->value[ms->i] == '\"')
		{
			ms->sub_tokens[*count] = ft_strdup("");
			if (!ms->sub_tokens[*count])
				free_ms(ms);
			(*count)++;
			ms->i++;
			return ;
		}
		split_dquot_subt2(ms, aux_t, count);
	}
	if (aux_t->value[ms->i] == '$')
		split_dolar_subt(ms, aux_t, count, '\0');
}

void	split_dquot_subt2(t_ms *ms, t_token *aux_t, int *count)
{
	int	pos;

	while (aux_t->value[ms->i] != '\"' && aux_t->value[ms->i])
	{
		pos = ms->i;
		while (aux_t->value[ms->i] != '\"' && aux_t->value[ms->i] != '$'
			&& aux_t->value[ms->i])
			ms->i++;
		ms->sub_tokens[*count] = ft_substr(aux_t->value,
				pos, ms->i - pos);
		if (!ms->sub_tokens[*count])
			free_ms(ms);
		(*count)++;
		if (aux_t->value[ms->i] == '$')
			split_dolar_subt(ms, aux_t, count, '\"');
	}
	if (aux_t->value[ms->i] == '\"')
		ms->i++;
}

void	split_dolar_subt(t_ms *ms, t_token *aux_t, int *count, char c)
{
	ms->i++;
	if (aux_t->value[ms->i] == '$' || aux_t->value[ms->i] == '0'
		|| aux_t->value[ms->i] == '#' || aux_t->value[ms->i] == '-')
	{
		ms->sub_tokens[*count] = ft_strdup("");
		if (!ms->sub_tokens[(*count)++])
			free_ms(ms);
		ms->i++;
	}
	else if (aux_t->value[ms->i] == '?')
	{
		ms->sub_tokens[*count] = ft_itoa(ms->exit_status);
		ms->i++;
		if (!ms->sub_tokens[(*count)++])
			free_ms(ms);
	}
	else if (ft_is_space(aux_t->value[ms->i]) || aux_t->value[ms->i] == c
		|| !ft_isalnum(aux_t->value[ms->i]))
	{
		ms->sub_tokens[*count] = ft_strdup("$");
		if (!ms->sub_tokens[(*count)++])
			free_ms(ms);
	}
	else
		check_env_split(ms, aux_t, count);
}
