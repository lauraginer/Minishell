/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:04:59 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/16 21:48:39 by lauragm          ###   ########.fr       */
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

/*int	main(int argc, char **args)
{
	(void)argc;
	builtin_pwd(args);
	return (0);
}*/