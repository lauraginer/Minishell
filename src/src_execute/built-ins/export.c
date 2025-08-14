/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:03:16 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/12 19:25:29 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	print_error_ex(char *arg, t_ms *ms)
{
	printf("export: %s: not a valid identifier\n", arg);
	ms->exit_status = 1;
}

int	add_to_env(char *var, t_list **my_env)
{
	t_list	*new_node;
	char	*new_var;

	new_var = ft_strdup(var);
	if (!new_var)
		return (1);
	new_node = ft_lstnew(new_var);
	if (!new_node)
	{
		free(new_var);
		return (1);
	}
	ft_lstadd_back(my_env, new_node);
	return (0);
}

static int	handle_no_args_export(t_list **my_env)
{
	t_list	*current_env;

	current_env = *my_env;
	print_env(&current_env);
	return (0);
}

static int	process_export_arg(char *arg, t_list **my_env, t_ms *ms)
{
	if (!is_correct(arg))
	{
		print_error_ex(arg, ms);
		return (1);
	}
	if (ft_strchr(arg, '='))
	{
		if (update_env_var(arg, my_env) != 0)
		{
			ms->exit_status = 1;
			printf("export: error: could not allocate memory\n");
			return (1);
		}
	}
	else if (env_exportable(arg, my_env) != 0)
	{
		ms->exit_status = 1;
		printf("export: error: could not allocate memory\n");
		return (1);
	}
	return (0);
}

int	builtin_export(char **args, t_list **my_env, t_ms *ms)
{
	int	i;

	i = 1;
	ms->exit_status = 0;
	if (!args[1])
		return (handle_no_args_export(my_env));
	while (args[i])
	{
		process_export_arg(args[i], my_env, ms);
		i++;
	}
	return (ms->exit_status);
}
