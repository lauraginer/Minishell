
#include "../../inc/minishell.h"


/*It checks if a given word matches an enviroment
	 variable to count it as subtoken*/
void	check_env_count(t_ms *ms, t_token *aux_t, int *count)
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
			(*count)++;
			break ;
		}
		tmp = tmp->next;
	}
	free (word);
}

/*It counts subtokens created by dolar sign*/
void	count_dolar_subtokens(t_ms *ms, t_token *aux_t, int *count, char c)
{
	ms->i++;
	if (aux_t->value[ms->i] == '$' || aux_t->value[ms->i] == '0'
		|| aux_t->value[ms->i] == '#' || aux_t->value[ms->i] == '-')
		ms->i++;
	else if (aux_t->value[ms->i] == '?')
	{
		(*count)++;
		ms->i++;
	}
	else if (ft_is_space(aux_t->value[ms->i]) || aux_t->value[ms->i] == c)
		(*count)++;
	else
		check_env_count(ms, aux_t, count);
}

/*It counts how many subtokens will be created 
	due to the expand (to allocate the memory correctly)*/
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
			pos = ms->i;
			while (aux_t->value[ms->i] != '\'')
				ms->i++;
			if (pos != ms->i)
				(*count)++;
			ms->i++;
		}
		count_subtokens2(ms, aux_t, count);
	}
}

/*Second part of count subtokens*/
void	count_subtokens2(t_ms *ms, t_token *aux_t, int *count)
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
				(*count)++;
			if (aux_t->value[ms->i] == '$')
				count_dolar_subtokens(ms, aux_t, count, '\"');
			ms->i++;
		}
	}
	if (aux_t->value[ms->i] == '$')
		count_dolar_subtokens(ms, aux_t, count, '\0');
	ms->i++;
}
