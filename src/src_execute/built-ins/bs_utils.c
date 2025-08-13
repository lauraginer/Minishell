/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:28:39 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/13 11:15:53 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	update_pwd_env(const char *old_dir)
{
	char	current_dir[PATH_MAX];

	if (getcwd(current_dir, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (setenv("OLDPWD", old_dir, 1) != 0)
	{
		perror("setenv OLDPWD");
		return (1);
	}
	if (setenv("PWD", current_dir, 1) != 0)
	{
		perror("setenv PWD");
		return (1);
	}
	return (0);
}

int	check_and_replace_env(t_list *current, char *name, int name_len, char *var)
{
	char	*env_entry;

	env_entry = (char *)current->content;
	if (ft_strncmp(env_entry, name, name_len) == 0
		&& (env_entry[name_len] == '=' || env_entry[name_len] == '\0'))
	{
		free(current->content);
		current->content = ft_strdup(var);
		if (!current->content)
			return (0);
		return (1);
	}
	return (0);
}

int	update_env_var(char *var, t_list **my_env)
{
	char	*name;
	char	*equal_sign;
	int		name_len;
	t_list	*current;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return (0);
	name_len = equal_sign - var;
	name = ft_substr(var, 0, name_len);
	if (!name)
		return (1);
	current = *my_env;
	while (current)
	{
		if (check_and_replace_env(current, name, name_len, var))
		{
			free(name);
			return (0);
		}
		current = current->next;
	}
	free(name);
	return (add_to_env(var, my_env));
}

void	print_env(t_list **my_env)
{
	t_list	*current_env;
	char	*env_var;
	char	*equal_pos;

	current_env = *my_env;
	while (current_env)
	{
		env_var = (char *)current_env->content;
		equal_pos = ft_strchr(env_var, '=');
		if (equal_pos)
		{
			*equal_pos = '\0';
			printf("declare -x %s=\"%s\"\n", env_var, equal_pos + 1);
			*equal_pos = '=';
		}
		else
			printf("declare -x %s\n", env_var);
		current_env = current_env->next;
	}
	return ;
}
