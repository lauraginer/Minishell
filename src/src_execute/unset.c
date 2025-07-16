/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:03:33 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/16 21:14:02 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	remove_env(char *var, t_list **my_env)
{
	t_list	*current;
	t_list	*prev;
	int		var_len;
	char	*env_entry;

	current = *my_env;
	prev = NULL;
	var_len = ft_strlen(var);
	while (current)
	{
		env_entry = (char *)current->content;
		if ((ft_strncmp(env_entry, var, var_len) == 0)
			&& (env_entry[var_len] == '=' || env_entry[var_len] == '\0'))
		{
			if (prev == NULL)
				*my_env = current->next;
			else
				prev->next = current->next;
			free(current->content);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

int	builtin_unset(char **args, t_list **my_env, t_ms *ms)
{
	int	i;

	i = 1;
	ms->exit_status = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		if (!is_correct(args[i]))
		{
			printf("unset: %s: not a valid identifier\n", args[i]);
			ms->exit_status = 1;
		}
		else
			remove_env(args[i], my_env);
		i++;
	}
	return (ms->exit_status);
}
