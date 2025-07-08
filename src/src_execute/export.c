/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:03:16 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/08 21:13:59 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void print_error_ex(char *arg)
{
	printf("export: %s: No such file or directory\n", arg);
	//ms->exit_status = 1;	
}
int is_correct(char *arg)
{
	int i;

	i = 1;
	if(!ft_isalpha(arg[0]) && arg[0] != '_')
		return(0);
	while(arg[i])
	{
		if(!ft_isalpha(arg[i]) && arg[i] != '_')
			return(0);
		i++;
	}
	return(1);
}
int builtin_export(char **args, t_list *my_env)
{
	t_list *current_env;
	int i;
	char *equal;

	current_env = my_env;
	equal = ft_strchr("=", args);
	i = 1;
	if(!args[1])
	{
		while(current_env)
		{
			printf("declare -x %s\n", (char *)current_env->content);
			current_env = current_env->next;
		}
		//ms->exit_status = 0;
	}
	while(args[i])
	{
		if(!is_correct(args))
		{
			print_error_ex(args)
			//ms->exit_status = 1;
		}
		
		i++;
	}
	if(args[1] && args[2] && args[3])
		print_error_ex(args);
	return(0);
}

