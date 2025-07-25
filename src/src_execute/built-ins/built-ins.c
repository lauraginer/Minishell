/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:09 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/25 02:28:01 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*para comprobar si un comando es builtin, Y si lo es, 
ejecútalo directamente sin hacer fork (esto es importante porque algunos built-ins
como cd o exit tienen que afectar directamente al shell, no a un hijo).*/
int is_builtin(char *cmd); //referencia a la estructura s_ast_node y dentro de ella a cmd

int execute_builtin(char **args, t_ms *ms)
{
	int result;

	result = 0;
	if (ft_strncmp(args[0], "echo", 5) == 0)
		result = builtin_echo(args, ms);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		result = builtin_cd(args, ms);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		result = builtin_pwd(args, ms);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		result = builtin_exit(args, ms);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		result = builtin_env(args, ms->my_env, ms);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		result = builtin_export(args, &ms->my_env, ms);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		result = builtin_unset(args, &ms->my_env, ms);
	
	ms->exit_status = result;
	return (result);
}

/* TODO: Una vez tengas el AST y estés en la fase de ejecución, harás algo como:
if (is_builtin(node->args[0]))
    execute_builtin(node->args);
else
{
	if(check_command_exists(cmd) == 0)
		execute_external_command(node->args);
	else
		//print error y exit
}
*/
    

