/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:04:53 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/16 22:04:02 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int builtin_echo(char **args)
{
	int i;
	int flag_n;
	int j;
	
	i = 1;
	flag_n = 1;
	if(!args[1])
	{
		write(1, "\n", 1);
		return(0);
	}
	if(args[1] && strcmp(args[1], "-n") == 0)
	{
		flag_n = 0;		
		i = 2; //empezamos en el segundo argumento
	}
	while(args[i])
	{
		j = 0;
		while(args[i][j])
		{
			write(1, &args[i][j], 1);
			j++;
		}
		if(args[i + 1]) //si hay más de un argumento
			write(1, " ", 1);
		i++;
	}
	if(flag_n)
		write(1, "\n", 1);
	return(0);
}

/*args[0] será "echo", mientras que args[1], args[2], etc. serán los argumentos reales del comando.
Antes de imprimir nada, revisa si los primeros argumentos son -n, -nnn, etc.
Puedes hacer un pequeño bucle que siga avanzando si los argumentos cumplen con ese patrón, si 
os detectas, guardas un flag newline = false.
Si no se encontró el flag -n, al final del todo debes imprimir un \n*/

int main(int argc, char **args)
{
    (void)argc;
    builtin_echo(args);
    return 0;
}