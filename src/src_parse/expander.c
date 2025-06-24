

#include "../../inc/minishell.h"

void	expander(t_list *my_env, t_ms *ms)
{
	t_list	*curr;
	t_token	*aux_t;
	int		i;
	int		pos;
	
	i = 0;
	aux_t = ms->tokens;
	curr = my_env;
	while (aux_t)
	{
		if (aux_t->type = TOKEN_WORD)
		{
			while (aux_t->value[i])
			{
				if ((aux_t->value[i] == '\"' || aux_t->value[i] == '$') && ms->s_quot == 0)
				{
					ms->exp_f = 1;
					break;
				}
				if (aux_t->value[i] == '\"' && ms->exp_f == 0)
					ms->s_quot = 1;
				i++;
			}
			if (ms->exp_f == 1)
			{
				i = 0;
				pos = i;
				while (aux_t->value[i])
				{

				}
			}
		}
		aux_t = aux_t->next;
	}
}
