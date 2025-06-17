/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:04:53 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/17 18:51:42 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	valid_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0); // contiene cualquier otra cosa (inválido)
}
int	builtin_echo(char **args)
{
	int	i;
	int	flag_n;
	int	j;

	i = 1;
	flag_n = 1;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[i] && valid_flag(args[i]))
	{
		flag_n = 0;
		i++;
	}
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			write(1, &args[i][j], 1);
			j++;
		}
		if (args[i + 1]) // si hay más de un argumento
			write(1, " ", 1);
		i++;
	}
	if (flag_n)
		write(1, "\n", 1);
	return (0);
}

/*args[0] será "echo", mientras que args[1], args[2],etc. serán los argumentos reales del comando.
Antes de imprimir nada, revisa si los primeros argumentos son -n, -nnn, etc.
Puedes hacer un pequeño bucle que siga avanzando si los argumentos cumplen con ese patrón, si
os detectas, guardas un flag newline = false.
Si no se encontró el flag -n, al final del todo debes imprimir un \n*/

int	main(int argc, char **args)
{
	(void)argc;
	builtin_echo(args);
	return (0);
}