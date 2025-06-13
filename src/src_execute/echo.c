/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:04:53 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/13 19:36:19 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_echo(char **args)
{
	int i;
	i = 0;
	
	while(args[1])
	{
		
	}
	
}

/*args[0] será "echo", mientras que args[1], args[2], etc. serán los argumentos reales del comando.
Antes de imprimir nada, revisa si los primeros argumentos son -n, -nnn, etc.
Puedes hacer un pequeño bucle que siga avanzando si los argumentos cumplen con ese patrón, si 
os detectas, guardas un flag newline = false.
Si no se encontró el flag -n, al final del todo debes imprimir un \n*/

int main()