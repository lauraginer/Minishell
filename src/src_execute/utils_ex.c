/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:37:03 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/09 00:42:28 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_free_split(char **split)
{
	int i;
	
	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char *manage_relative_or_absolute_path(char *cmd)
{
	if(cmd[0] == '/' || cmd[0] == '.' || ft_strchr(cmd, '/'))
	{
		if(access(cmd, F_OK | X_OK) == 0)
			return(ft_strdup(cmd));
		return(NULL);
	}
	return(NULL);
}

int is_string_numeric(char *filename)
{
	int i;
	
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

int get_input_fd(char *filename, t_ms *ms)
{
	int fd;
	
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