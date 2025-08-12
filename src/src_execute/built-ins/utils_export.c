/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:24:25 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/12 19:26:31 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_correct(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	env_exportable(char *var, t_list **my_env)
{
	t_list	*current;
	char	*env;
	char	*equal_sign;
	size_t	var_len;

	current = *my_env;
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
		var_len = equal_sign - var;
	else
		var_len = ft_strlen(var);
	while (current)
	{
		env = (char *)current->content;
		if (ft_strncmp(env, var, var_len) == 0 && (env[var_len] == '='
				|| env[var_len] == '\0'))
			return (0);
		current = current->next;
	}
	return (add_to_env(var, my_env));
}
