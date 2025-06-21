/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:35:35 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/20 21:49:11 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int builtin_exit(char **args)
{
	if(args[1])
	{
		if (args[2])
		{
			ft_printf("exit\n");
			ft_printf("exit: too many arguments\n");
		}
		if (!args[1] && !(ft_isalnum(ft_atoi(args[1])))) //en este caso sale con el código 255 por convención
		{
			ft_printf("exit\n");
			ft_printf("exit: '%s': numeric argument required\n", args[1]);
			//sale por convención
			return(0);
		}	
		else
			//actua el comando tal y como siempre, siempre y cuando sea un numero digito
		return(0);
	}
	
}