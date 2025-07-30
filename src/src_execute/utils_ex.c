/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:37:03 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/30 19:27:57 by lauragm          ###   ########.fr       */
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

char *manage_relative_or_absolute_path(char *cmd)
{
	if(cmd[0] == '/' || cmd[0] == '.' || ft_strchr(cmd, '/'))
	{
		if(access(cmd, F_OK | X_OK) == 0) //verifica si existe y es ejecutable
			return(ft_strdup(cmd));
		return(NULL);
	}
	return(NULL);
}

// Función recursiva simplificada
static void debug_ast_recursive(t_ast_node *node, int depth)
{
	int i;
	
	if (!node)
		return;
	
	// Mostrar indentación según profundidad
	for (i = 0; i < depth; i++)
		printf("  ");
	
	// Mostrar tipo de nodo
	if (node->type == TOKEN_PIPE)
		printf("PIPE\n");
	else if (node->type == TOKEN_WORD && node->args && node->args[0])
	{
		printf("CMD: %s", node->args[0]);
		if (node->args[1])
		{
			int j = 1;
			while (node->args[j])
			{
				printf(" %s", node->args[j]);
				j++;
			}
		}
		printf("\n");
	}
	else
		printf("NODE (type=%d)\n", node->type);
	
	// Mostrar hijos
	if (node->left)
		debug_ast_recursive(node->left, depth + 1);
	if (node->right)
		debug_ast_recursive(node->right, depth + 1);
}

//Función básica para debuggear el AST - versión simplificada
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
