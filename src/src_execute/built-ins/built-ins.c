/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:09 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/25 13:12:26 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*para comprobar si un comando es builtin, Y si lo es, 
ejecútalo directamente sin hacer fork (esto es importante porque algunos built-ins
como cd o exit tienen que afectar directamente al shell, no a un hijo).*/

int is_builtin(char *cmd)
{
	if(!cmd)
		return (0);
	if(ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if(ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if(ft_strncmp(cmd, "pwd", 4) == 0)
		return(1);
	if(ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if(ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if(ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if(ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int execute_builtin(t_ast_node *node, t_ms *ms)
{
	int result;

	result = 0;
	if(ft_strncmp(node->args[0], "echo", 5) == 0)
		result = builtin_echo(node->args, ms);
	else if(ft_strncmp(node->args[0], "cd", 3) == 0)
		result = builtin_cd(node->args, ms);
	else if(ft_strncmp(node->args[0], "pwd", 4) == 0)
		result = builtin_pwd(node->args, ms);
	else if(ft_strncmp(node->args[0], "exit", 5) == 0)
		result = builtin_exit(node->args, ms);
	else if(ft_strncmp(node->args[0], "env", 4) == 0)
		result = builtin_env(node->args, ms->my_env, ms);
	else if(ft_strncmp(node->args[0], "export", 7) == 0)
		result = builtin_export(node->args, &ms->my_env, ms);
	else if(ft_strncmp(node->args[0], "unset", 6) == 0)
		result = builtin_unset(node->args, &ms->my_env, ms);
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
    

