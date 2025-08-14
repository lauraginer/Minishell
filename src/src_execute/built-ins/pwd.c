/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:04:59 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/12 18:56:45 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	builtin_pwd(char **args, t_ms *ms)
{
	char	buffer[PATH_MAX];

	(void)args;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
	{
		ms->exit_status = 1;
		perror("getcwd");
	}
	ms->exit_status = 0;
	return (0);
}
