/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/14 19:12:58 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(char *name, t_list *my_env)
{
	t_list	*current;
	size_t	len;

	current = my_env;
	len = ft_strlen(name);
	while (current)
	{
		if (ft_strncmp(current->content, name, len) == 0
			&& ((char *)current->content)[len] == '=')
			return (((char *)current->content) + len + 1);
		current = current->next;
	}
	return (NULL);
}

static char	*search_in_directory(char *dir, char *cmd)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(dir, "/");
	if (!temp_path)
		return (NULL);
	full_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK | X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_path_dirs(char **path_dirs, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = search_in_directory(path_dirs[i], cmd);
		if (full_path)
		{
			ft_free_split(path_dirs);
			return (full_path);
		}
		i++;
	}
	ft_free_split(path_dirs);
	return (NULL);
}

char	*get_command_path(char *cmd, t_list *my_env)
{
	char	*path_env;
	char	**path_dirs;
	char	*full_path;
	int		saved_errno;

	full_path = manage_relative_or_absolute_path(cmd);
	if (full_path)
		return (full_path);
	saved_errno = errno;
	if (saved_errno == EACCES || saved_errno == EISDIR)
		return (NULL);
	path_env = get_env_value("PATH", my_env);
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	return (search_in_path_dirs(path_dirs, cmd));
}
