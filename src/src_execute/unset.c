/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:03:33 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/15 20:30:07 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int remove_env(char *var, t_list **my_env);
builtin_unset(char **args, t_list **my_env, t_ms *ms)
{
	t_list *current_env;

	current_env = *my_env;
	ms->exit_status = 0;
	
}
//NO GESTIONA SI LA NOMENCLATURA ES CORRECTA