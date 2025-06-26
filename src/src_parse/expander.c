
#include "../../inc/minishell.h"

/*
	ms->exp_f --> flag to confirm there's something to expand (' , " , $)
				It let me know if I have to resize the value of the token
	
	quot --> to define what type of quote is the current quote
	ms->s_quot  --> tal vez no haga falta
*/


/*It tells if there's any quote or $*/
int	is_exp_token(char c)
{
	if (c == '\"' || c == '\'' || c == '$')
		return (1);
	return (0);
}

/*It change ms->exp_f to 1 if is_exp_token is true,
 so that you know there's something to expand*/
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

/*It checks if a given word is an enviroment word*/
void	check_env(t_ms *ms, t_token *aux_t, int *count)
{
	char	*word;
	int		i;
	t_list	*tmp;

	tmp = ms->my_env;
	i = 0;
	while (ft_isalnum(aux_t->value[ms->i]) || aux_t->value == '_')
		i++;
	ms->i += i;
	if (i == 0)
		return ;
	word = malloc(sizeof(char) * (i + 1));
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

int	count_dolar_subtokens(t_ms *ms, t_token *aux_t, int *count, char c)
{
	int	pos;

	ms->i++;
	pos = ms->i;
	if (aux_t->value[ms->i] == '$' || aux_t->value[ms->i] == '0'
		|| aux_t->value[ms->i] == '#' || aux_t->value[ms->i] == '-')
		ms->i++;
	else if (aux_t->value[ms->i] == '?')
	{
		*(count)++;
		ms->i++;
	}
	else if (ft_is_space(aux_t->value[ms->i]) || aux_t->value[ms->i] == c)
		(*count)++;
	else
		check_env(ms, aux_t, count);
}

/*It counts how many subtokens will be created 
	due to the expand (to allocate the memory correctly)*/
int	count_subtokens(t_ms *ms, t_token *aux_t)
{
	int	*count;
	int	pos;

	*count = 0;
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
		count += count_subtokens2(ms, aux_t, count);
	}
	return (count);
}

int	count_subtokens2(t_ms *ms, t_token *aux_t, int *count)
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
				count += count_dolar_subtokens(ms, aux_t, count, '\"');
			ms->i++;
		}
	}
	if (aux_t->value[ms->i] == '$')
		count += count_dolar_subtokens(ms, aux_t, count, '\0');
	ms->i++;
	return (count);
}

void	expander(t_ms *ms)
{
	t_list	*curr;
	t_token	*aux_t;
	int		pos;
	int		count;

	ms->i = 0;
	aux_t = ms->tokens;
	curr = ms->my_env;
	while (aux_t)
	{
		if (aux_t->type == TOKEN_WORD)
		{
			count = 0;
			search_expand(ms, aux_t);
			if (ms->exp_f == 1)
				count += count_subtokens(ms, aux_t);
		}
		aux_t = aux_t->next;
	}
}
