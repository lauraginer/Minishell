/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:37:03 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/25 14:22:17 by lauragm          ###   ########.fr       */
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

/* Función auxiliar para crear un nodo AST temporal
static t_ast_node *create_temp_ast_node(char **args)
{
	t_ast_node *node;
	
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = TOKEN_WORD;
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Función auxiliar para liberar array de argumentos
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

/* Función auxiliar de parse para extraer argumentos de los tokens
static char **extract_args_from_tokens(t_ms *ms, int *arg_count)
{
	t_token *current;
	char **args;
	int i;

	// Verificar que solo tengamos tokens WORD (sin pipes/redirecciones)
	current = ms->tokens;
	*arg_count = 0;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			(*arg_count)++;
		else
		{
			printf("Error: pipes y redirecciones aún no implementados\n");
			return (NULL);
		}
		current = current->next;
	}
	
	if (*arg_count == 0)
		return (NULL);
		
	// Crear array de argumentos
	args = malloc(sizeof(char*) * (*arg_count + 1));
	if (!args)
		return (NULL);
		
	// Llenar el array con los valores de los tokens
	current = ms->tokens;
	i = 0;
	while (current && i < *arg_count)
	{
		if (current->type == TOKEN_WORD)
		{
			args[i] = ft_strdup(current->value);
			if (!args[i])
			{
				// Liberar memoria ya asignada en caso de error
				while (--i >= 0)
					free(args[i]);
				free(args);
				return (NULL);
			}
			i++;
		}
		current = current->next;
	}
	args[*arg_count] = NULL;
	return (args);
}*/

/*Función temporal para ejecutar comandos simples (sin pipes ni redirecciones)
void execute_simple_tokens(t_ms *ms)
{
	char **args;
	int arg_count;
	t_ast_node *temp_node;
	t_ms *ms_ptr;

	if (!ms->tokens)
		return;
		
	// Extraer argumentos de los tokens
	args = extract_args_from_tokens(ms, &arg_count);
	if (!args)
		return;
		
	// Crear nodo AST temporal (reutilizable para builtin y comando externo)
	temp_node = create_temp_ast_node(args);
	if (!temp_node)
	{
		free_args_array(args);
		return;
	}
	
	// Ejecutar según el tipo de comando
	if (is_builtin(args[0]))
	{
		execute_builtin(temp_node, ms);
	}
	else
	{
		ms_ptr = ms;
		execute_external_command(&temp_node, &ms_ptr, ms->my_env);
	}
	
	// Limpiar memoria
	free(temp_node);
	free_args_array(args);
}*/
