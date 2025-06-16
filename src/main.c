/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:49:30 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/16 17:03:56 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


t_list *copy_env_var(char **envp)
{
	int	i;
	t_list *new_node;
	t_list *env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		new_node = ft_lstnew(ft_strdup(envp[i]));
		// MANEJO DE ERRORES
		ft_lstadd_back(&env, new_node);
		i++;
	}
	return (env);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env;

	env = copy_env_var(envp);
	while (argc && argv)
	{
		input = readline("minishell> ");
		if (*input)
			add_history(input);
		else
			break;
		free (input);
	}
}
