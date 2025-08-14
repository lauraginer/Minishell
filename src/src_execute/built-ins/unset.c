/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:03:33 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/12 18:44:30 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	remove_env(char *var, t_list **my_env)
{
	t_list	*current;
	t_list	*prev;
	int		var_len;

	current = *my_env;
	prev = NULL;
	var_len = ft_strlen(var);
	while (current)
	{
		if ((ft_strncmp((char *)current->content, var, var_len) == 0)
			&& (((char *)current->content)[var_len] == '='
			|| ((char *)current->content)[var_len] == '\0'))
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
