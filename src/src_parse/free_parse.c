

#include "../../inc/minishell.h"

void	free_env_list(t_list *my_env)
{
	t_list	*aux;

	while (my_env)
	{
		aux = my_env->next;
		free (my_env->content);
		free (my_env);
		my_env = aux;
	}
}

void	free_token_list(t_token *tokens)
{
	t_token	*aux;

	while (tokens)
	{
		aux = tokens->next;
		free (tokens->value);
		free (tokens);
		tokens = aux;
	}
}

void	free_ms(t_ms *ms)
{
	if (ms->input)
		free (ms->input);
	if (ms->tokens)
		free_token_list(ms->tokens);
	if (ms->my_env)
		free_env_list(ms->my_env);
	free(ms);
}
