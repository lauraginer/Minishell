/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:32:24 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/06/17 09:34:55 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void free_env_list(t_list *env)
{
	t_list *aux;
	
	while (env)
	{
		aux = env->next;
		free (env->content);
		free (env);
		env = aux;
	}
}
