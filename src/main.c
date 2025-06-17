/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:49:30 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/17 17:51:46 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void lexer(t_list *env, char *input)
{
	t_token *tokens;
	t_token *node;
}

t_list *copy_env_var(char **envp)
{
	int		i;
	t_list	*new_node;
	t_list	*env;
	char	*copy;

	i = -1;
	env = NULL;
	while (envp[++i])
	{
		copy = ft_strdup(envp[i]);
		if (!copy)
		{
			free_env_list(env);
			return (NULL);
		}
		new_node = ft_lstnew(copy);
		if (!new_node)
		{
			free(copy);
			free_env_list(env);
			return (NULL);
		}
		ft_lstadd_back(&env, new_node);
	}
	return (env);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env;

	env = copy_env_var(envp);
	if (!env)
		exit (1); //crear un enum de errores y meter el correspondiente aqui
	while (argc && argv)
	{
		input = readline("minishell> ");
		if (*input)
			add_history(input);
		else
			break;
		lexer(env, input);
		free (input);
	}
	free_env_list(env);
}
