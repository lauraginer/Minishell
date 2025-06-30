

#include "../../inc/minishell.h"

/*It split tokens inside simple quotes*/
void	split_squot_subt(t_ms *ms, t_token *aux_t, int *count)
{
	int	pos;
	
	ms->i++;
	pos = ms->i;
	while (aux_t->value[ms->i] != '\'')
		ms->i++;
	if (pos != ms->i)
	{
		ms->sub_tokens[*count] = ft_substr(aux_t->value,
				pos, ms->i - pos);
		(*count)++;
		if (!ms->sub_tokens)
			free_ms(ms);
	}
	ms->i++;
}

/*It split tokens not contained inside $, simple of double quotes*/
void	split_norm_subt(t_ms *ms, t_token *aux_t, int *count)
{
	int	pos;

	pos = ms->i;
	while (aux_t->value[ms->i] && !is_exp_token(aux_t->value[ms->i]))
		ms->i++;
	if (pos != ms->i)
	{
		ms->sub_tokens[*count] = ft_substr(aux_t->value, pos, ms->i - pos);
		(*count)++;
		if (!ms->sub_tokens)
			free_ms(ms);
	}
}

/*It split tokens inside double quotes*/
void	split_dquot_subt(t_ms *ms, t_token *aux_t, int *count)
{
	int	pos;

	if (aux_t->value[ms->i] == '\"')
	{
		ms->i++;
		while (aux_t->value[ms->i] != '\"')
		{
			pos = ms->i;
			while (aux_t->value[ms->i] != '\"' && aux_t->value[ms->i] != '$')
				ms->i++;
			if (pos != ms->i)
			{
				ms->sub_tokens[(*count)++] = ft_substr(aux_t->value,
						pos, ms->i - pos);
				if (!ms->sub_tokens)
					free_ms(ms);
			}
			if (aux_t->value[ms->i] == '$')
				split_dolar_subt(ms, aux_t, count, '\"');
			ms->i++;
		}
	}
	if (aux_t->value[ms->i] == '$')
		split_dolar_subt(ms, aux_t, count, '\0');
	ms->i++;
}

/*It split tokens after dolar sign*/
void	split_dolar_subt(t_ms *ms, t_token *aux_t, int *count, char c)
{
	ms->i++;
	if (aux_t->value[ms->i] == '$' || aux_t->value[ms->i] == '0'
		|| aux_t->value[ms->i] == '#' || aux_t->value[ms->i] == '-')
		ms->i++;
	else if (aux_t->value[ms->i] == '?')
	{
		ms->sub_tokens[*count] = ft_itoa(ms->exit_status);
		ms->i++;
		(*count)++;
		if (!ms->sub_tokens)
			free_ms(ms);
	}
	else if (ft_is_space(aux_t->value[ms->i]) || aux_t->value[ms->i] == c)
	{
		ms->sub_tokens[*count] = ft_strdup("$");
		(*count)++;
		if (!ms->sub_tokens)
			free_ms(ms);
	}
	else
		check_env_split(ms, aux_t, count);
}

/*It checks if a given word matches an enviroment
	 variable to split it as subtoken*/
void	check_env_split(t_ms *ms, t_token *aux_t, int *count)
{
	char	*word;
	int		i;
	t_list	*tmp;

	tmp = ms->my_env;
	i = 0;
	while (ft_isalnum(aux_t->value[ms->i]) || aux_t->value[ms->i] == '_')
		i++;
	if (i == 0)
		return ;
	word = ft_substr(aux_t->value, ms->i, i);
	if (!word)
		free_ms(ms);
	ms->i += i;
	i = 0;
	while (tmp)
	{
		if (ft_strncmp(word, (char *)(tmp->content), ft_strlen(word)) == 0)
		{
			ms->sub_tokens[*count] = word;
			(*count)++;
			break ;
		}
		tmp = tmp->next;
	}
}