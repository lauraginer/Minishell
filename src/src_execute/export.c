/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:03:16 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/07 22:38:24 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void print_error_ex(int flag)
{
	if(flag > 0)
		printf("export: %s: No such file or directory\n", args[1]);
	//ms->exit_status = 0;	
}
int builtin_export(char **args, t_list *my_env)
{
	t_list *current_env;

	current_env = my_env;
	
	if(!args[1])
	{
		while(current_env)
		{
			printf("declare -x %s\n", (char *)current_env->content);
			current_env = current_env->next;
		}
		//ms->exit_status = 0;
	}
	if(args[1] && args[2])
	{
		
	}
	if(args[1] && args[2] && args[3])
	{
		printf("export: %s: No such file or directory\n", args[1]);
		//ms->exit_status = 0;
	}
	return(0);
}
int is_correct(char *arg)
{
	int i;

	i = 0;
	if(arg[i])
	{
		if(control_nums(arg[i]))
			print_error_ex = 1;
	}
}
//con argumentos hay que analizar uno por uno, 