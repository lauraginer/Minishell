/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:55:54 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/19 22:18:24 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_env(char **args, t_list *my_env)
{
	t_list	*current_env;
	
	current_env = my_env;
	if (args[1])
	{
		if (args[1][0] == '-' && args[1][1] == '-')
			ft_printf("env: unrecognized option '%s'\n", args[1]);
		else if (args[1][0] == '-')
			ft_printf("env: invalid option -- '%c'\n", args[1][1]);
		else
			ft_printf("env: '%s': No such file or directory\n", args[1]);
		return (1);
	}
	while (current_env)
	{
		ft_printf("%s\n", (char *)current_env->content);
		current_env = current_env->next;
	}
	return(0);
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_list *my_env;
	
	(void)argc;
	my_env = copy_env_var(envp);
	builtin_env(argv, my_env); // Pasamos argumentos y variables de entorno
	return (0);
}
*/