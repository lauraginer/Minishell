/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:55:54 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/18 21:38:11 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	if (envp[1])
	{
		if (envp[1][0] == '-' && envp[1][1] == '-')
			ft_printf("env: unrecognized option '%s'\n", envp[1]);
		else if (envp[1][0] == '-')
			ft_printf("env: invalid option -- '%c'\n", envp[1][1]);
		else
			ft_printf("env: '%s': No such file or directory\n", envp[1]);
		return (1);
	}
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
			// Necesitas las variables de entorno para literalmente imprimirlas
		i++;
	}
	return(0);
}

int	main(int argc, char **envp)
{
	(void)argc;
	builtin_env(envp); // en este caso se pasa las variables de entorno, no argumentos
	return (0);
}