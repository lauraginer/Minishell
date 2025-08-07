/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:55:54 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/06 18:12:08 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	builtin_env(char **args, t_list *my_env, t_ms *ms)
{
	t_list	*current_env;

	current_env = my_env;
	if (args[1])
	{
		if (args[1][0] == '-' && args[1][1] == '-')
			printf("env: unrecognized option '%s'\n", args[1]);
		else if (args[1][0] == '-')
			printf("env: invalid option -- '%c'\n", args[1][1]);
		else
			printf("env: '%s': No such file or directory\n", args[1]);
		ms->exit_status = 1;
		return (1);
	}
	while (current_env)
	{
		char *env_var = (char *)current_env->content;
		if (ft_strchr(env_var, '='))
			printf("%s\n", env_var);
		current_env = current_env->next;
	}
	ms->exit_status = 0;
	return (0);
}
