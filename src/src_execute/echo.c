/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:04:53 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/18 21:30:06 by lginer-m         ###   ########.fr       */
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
void	print_arg(char *arg)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		write(1, &arg[j], 1);
		j++;
	}
}

int	builtin_echo(char **args)
{
	int	i;
	int	flag_n;

	i = 1;
	flag_n = 1;
	if (!args[1])
		return (write(1, "\n", 1), 0);
	while (args[i] && valid_flag(args[i]))
	{
		flag_n = 0;
		i++;
	}
	while (args[i])
	{
		print_arg(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag_n)
		write(1, "\n", 1);
	return (0);
}

int	main(int argc, char **args)
{
	(void)argc;
	builtin_echo(args);
	return (0);
}