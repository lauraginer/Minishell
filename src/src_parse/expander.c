
#include "../../inc/minishell.h"

int	is_exp_token(char c)
{
	if (c == '\"' || c == '\'' || c == '$')
		return (1);
	return (0);
}

void	search_expand(t_ms *ms, t_token *aux_t)
{
	while (aux_t->value[ms->i])
	{
		if (is_exp_token(aux_t->value[ms->i]))
		{
			ms->exp_f = 1;
			break ;
		}
		ms->i++;
	}
}

void	split_sub_token(t_ms *ms, t_token *aux_t, int *count)
{
	if ((*count) == 0)
		return ;
	ms->sub_tokens = ft_calloc((*count) + 1, sizeof(char *));
	if (!ms->sub_tokens)
		free_ms(ms);
	ms->i = 0;
	(*count) = 0;
	while (aux_t->value[ms->i])
	{
		split_norm_subt(ms, aux_t, count);
		if (aux_t->value[ms->i] == '\'')
			split_squot_subt(ms, aux_t, count);
		split_dquot_subt(ms, aux_t, count);
	}
	ms->sub_tokens[*count] = NULL;
}

void	join_subtokens(t_ms *ms, t_token *aux_t)
{
	char	*new_value;
	char	*tmp;
	int		i;

	i = 0;
	new_value = ft_strdup(ms->sub_tokens[i]);
	if (!new_value)
		free_ms(ms);
	while (ms->sub_tokens[i + 1])
	{
		tmp = new_value;
		new_value = ft_strjoin(new_value, ms->sub_tokens[i + 1]);
		if (!new_value)
		{
			free(tmp);
			free_ms(ms);
		}
		free(tmp);
		i++;
	}
	free_subtokens(ms->sub_tokens);
	free(aux_t->value);
	aux_t->value = new_value;
}

void	expander(t_ms *ms)
{
	t_token	*aux_t;
	int		*count;

	ms->i = 0;
	aux_t = ms->tokens;
	count = malloc (sizeof(int));
	if (!count)
		free_ms(ms);
	while (aux_t)
	{
		if (aux_t->type == TOKEN_WORD)
		{
			ms->i = 0;
			(*count) = 0;
			ms->exp_f = 0;
			search_expand(ms, aux_t);
			if (ms->exp_f == 1)
			{
				count_subtokens(ms, aux_t, count);
				split_sub_token(ms, aux_t, count);
				join_subtokens(ms, aux_t);
			}
		}
		aux_t = aux_t->next;
	}
	free(count);
	print_tokens(ms);
}
