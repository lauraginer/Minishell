/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:35:35 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/25 18:29:33 by lginer-m         ###   ########.fr       */
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
int	builtin_exit(char **args)
{
	int exit_status; // añadir a una lista general

	exit_status = 0;
	printf("exit\n");
	if (args[1])
	{
		if (!control_nums(args[1]))
			// en este caso sale con el código 255 por convención
		{
			printf("exit: '%s': numeric argument required\n", args[1]);
			// sale por convención
			exit_status = 255;
			return (255);
		}
		else if (args[2])
		{
			printf("exit: too many arguments\n");
			exit_status = 1;
		}
		else
		{
			exit_status = ft_atoi(args[1]) % 256;
			return (ft_atoi(args[1]) % 256);
		}
		// actua el comando tal y como siempre, siempre y cuando sea un numero digito
	}
	return (0);
	/*importante la variable exit(valor de retorno, 
	hay que actualizarlo conforme cada opcion Y SIEMPRE en comandos/builtins) actualiza tambien
	cuando sea mayor de 255, porque vuelve a uno y el valor de retorno es distinto,
	el exit solo se hace en un proceso padre*/

	// return(unsigned char(args[1]))
}