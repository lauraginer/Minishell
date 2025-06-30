
#include "../../inc/minishell.h"

/*
	ms->exp_f --> flag to confirm there's something to expand (' , " , $)
				It let me know if I have to resize the value of the token
	
	quot --> to define what type of quote is the current quote
	ms->s_quot  --> tal vez no haga falta
*/

//AÑADIR char **subtokens; a estructura principal

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

/*It splits the token in sub_tokens if needed*/
void	split_sub_token(t_ms *ms, t_token *aux_t, int *count)
{
	if ((*count) == 0)
		return ;
	ms->sub_tokens = malloc(sizeof(char *) * ((*count) + 1));
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
/*It joins the subtokens splitted*/
void	join_subtokens(t_ms *ms, t_token *aux_t)
{
	char	*new_value;
	char	*tmp;
	int		i;

	i = 0;
	new_value = ms->sub_tokens[i];
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


/*main function to expand variables*/
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
			(*count) = 0;
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
	print_tokens(ms);
}
