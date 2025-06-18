/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:04:59 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/18 21:37:01 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_pwd(char **args)
{
	char	buffer[PATH_MAX];

	(void)args;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
		perror("getcwd");
	return (0);
}

int	main(int argc, char **args)
{
	(void)argc;
	builtin_pwd(args);
	return (0);
}