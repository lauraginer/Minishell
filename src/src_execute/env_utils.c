/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:10:00 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/19 22:07:35 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Crea una copia de las variables de entorno en una lista enlazada
** @param envp Array de strings con las variables de entorno
** @return Lista enlazada con las variables de entorno copiadas
*/
t_list	*copy_env_var(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = ft_lstnew(ft_strdup(envp[i]));
		if (!new_node)
		{
			// Liberar la lista si hay error
			while (env_list)
			{
				new_node = env_list->next;
				free(env_list->content);
				free(env_list);
				env_list = new_node;
			}
			return (NULL);
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

/*
** Libera la memoria de la lista de variables de entorno
** @param env_list Lista enlazada con las variables de entorno
*/
void	free_env_list(t_list *env_list)
{
	t_list	*current;
	t_list	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}
