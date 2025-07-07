/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:35:35 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/05 16:18:05 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	control_nums(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
int	builtin_exit(char **args, t_ms *ms)
{
	int exit_code;

	printf("exit\n");
	
	if (!args || !args[0]) //verificación de seguridad para el test, luego QUITAS
		return (1);
		
	if (args[1])
	{
		if (!control_nums(args[1]))
		{
			printf("exit: '%s': numeric argument required\n", args[1]);
			ms->exit_status = 255;
			exit(ms->exit_status); // Salimos con código 255
		}
		else if (args[2])
		{
			printf("exit: too many arguments\n");
			ms->exit_status = 1;
			return (ms->exit_status); // No salimos, pero devolvemos estado de error
		}
		else
		{
			exit_code = ft_atoi(args[1]) % 256;
			ms->exit_status = exit_code;
			exit(ms->exit_status);
		}
	}
	exit(ms->exit_status);
}