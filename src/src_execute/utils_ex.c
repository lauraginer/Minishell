/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:37:03 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/06 22:36:16 by lauragm          ###   ########.fr       */
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

char *get_heredoc_delimiter(t_ast_node *node, t_ms *ms)
{
	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ms->exit_status = 1;
		return (NULL);
	}
	return (node->right->args[0]);
}

