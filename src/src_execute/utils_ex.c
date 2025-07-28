/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:37:03 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/28 14:34:10 by lauragm          ###   ########.fr       */
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

// Función básica para debuggear el AST - versión simplificada
void debug_ast(t_ast_node *root)
{
	printf("\n🌳 AST DEBUG:\n");
	if (!root)
	{
		printf("❌ AST is NULL\n\n");
		return;
	}
	debug_ast_recursive(root, 0);
	printf("🌳 END DEBUG\n\n");
}
