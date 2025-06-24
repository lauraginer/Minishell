

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

void	free_parse(t_parse *parse)
{
	if (parse->input)
		free (parse->input);
	if (parse->tokens)
		free_token_list(parse->tokens);
	free(parse);
}
