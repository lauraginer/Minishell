/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:37:03 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/25 19:51:11 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_free_split(char **split)
{
	int i;
	
	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*Función auxiliar para liberar array de argumentos
static void free_args_array(char **args)
{
	int i;
	
	if (!args)
		return;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}*/
