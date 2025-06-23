/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:35:35 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/23 21:36:23 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int control_nums(char *str)
{
	int i;

	i = 0;
	if(str[i] == '-' || str[i] == '+')
		i++;
	while(str[i])
	{
		if(!ft_isdigit(str[i]));
			return(0);
		i++;	
	}
	return(1);
}
int builtin_exit(char **args)
{
	if(args[1])
	{
		if (args[2])
		{
			printf("exit\n");
			printf("exit: too many arguments\n");
		}
		if (!args[1] && !(control_nums(args[1]))) //en este caso sale con el código 255 por convención
		{
			printf("exit\n");
			printf("exit: '%s': numeric argument required\n", args[1]);
			//sale por convención
			return(255);
		}	
		else
			//actua el comando tal y como siempre, siempre y cuando sea un numero digito
		return(0);
	}

	/*importante la variable exit(valor de retorno, hay que actualizarlo conforme cada opcion Y SIEMPRE en comandos/builtins),
	 el exit solo se hace en un proceso padre*/
	
}