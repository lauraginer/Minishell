/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:20:00 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/13 12:36:05 by lauragm          ###   ########.fr       */
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

int	handle_cd_home(t_ms *ms)
{
	int	result;

	result = handle_home_cases();
	if (result != 0)
		ms->exit_status = 1;
	else
		ms->exit_status = 0;
	return (result);
}

int	special_case(char *str)
{
	if (ft_strncmp(str, "--", 2) == 0 && str[2] == '\0')
		return (handle_home_cases());
	else if (ft_strncmp(str, "~", 1) == 0 && str[1] == '\0')
		return (handle_home_cases());
	else if (str[0] == '-' && str[1] == '-' && str[2])
	{
		printf("cd: -%c: invalid option\n", str[2]);
		return (1);
	}
	return (-1);
}
