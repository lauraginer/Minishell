

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

void	free_subtokens(char **sub_tokens)
{
	int	i;

	i = 0;
	while (sub_tokens[i])
	{
		free(sub_tokens[i]);
		i++;
	}
	free(sub_tokens);
}

void	free_ast(t_ast_node *ast)
{
	int	i;

	i = 0;
	if (ast->args)
	{
		while (ast->args[i])
		{
			free(ast->args[i]);
			i++;
		}
		free(ast->args);
	}
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
}

void	free_ms(t_ms *ms)
{
	int	exit_status;
	
	exit_status = ms->exit_status;
	if (ms->input)
		free (ms->input);
	if (ms->tokens)
		free_token_list(ms->tokens);
	if (ms->my_env)
		free_env_list(ms->my_env);
	if (ms->sub_tokens)
		free_subtokens(ms->sub_tokens);
	if (ms->f_ast_node)
		free_ast(ms->f_ast_node);
	free(ms);
	exit(exit_status);
}
