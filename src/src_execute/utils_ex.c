/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:37:03 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/14 19:45:42 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*manage_relative_or_absolute_path(char *cmd)
{
	struct stat	statbuf;

	if (!(cmd[0] == '/' || cmd[0] == '.' || ft_strchr(cmd, '/')))
		return (NULL);
	if (access(cmd, F_OK) != 0)
	{
		errno = ENOENT;
		return (NULL);
	}
	if (stat(cmd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		errno = EISDIR;
		return (NULL);
	}
	if (access(cmd, X_OK) != 0)
	{
		errno = EACCES;
		return (NULL);
	}
	return (ft_strdup(cmd));
}

int	is_string_numeric(char *filename)
{
	int	i;

	if (!filename || !filename[0])
		return (0);
	i = 0;
	while (filename[i])
	{
		if (!ft_isdigit(filename[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_input_fd(char *filename, t_ms *ms)
{
	int	fd;

	if (is_string_numeric(filename))
		fd = ft_atoi(filename);
	else
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			perror(filename);
			ms->exit_status = 1;
			return (-1);
		}
	}
	return (fd);
}

char	**get_env_arr(t_ms *ms, t_list *my_env)
{
	char	**envp;
	int		i;
	t_list	*aux;

	i = ft_lstsize(my_env);
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		free_ms(ms);
	aux = my_env;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(((char *)aux->content));
		if (!envp[i])
		{
			free_double_char(envp);
			free_ms(ms);
		}
		aux = aux->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
