/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:09 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/05 16:51:27 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int builtin_cd(char **args);
int builtin_pwd(char **args);
int builtin_exit(char **args, t_ms *ms);
int builtin_env(char **envp);
int builtin_export(char **args);
int builtin_unset(char **args);

/*para comprobar si un comando es builtin, Y si lo es, 
ejecútalo directamente sin hacer fork (esto es importante porque algunos built-ins
como cd o exit tienen que afectar directamente al shell, no a un hijo).*/
int is_builtin(char *cmd);

int execute_builtin(char **args, t_ms *ms)
{
	int result;

	result = 0;
	if (ft_strncmp(args[0], "echo", 5) == 0)
		result = builtin_echo(args, ms);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		result = builtin_cd(args, ms);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		result = builtin_pwd(args);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		result = builtin_exit(args, ms);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		result = builtin_env(args, ms->my_env);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		result = builtin_export(args);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		result = builtin_unset(args);
	
	ms->exit_status = result;
	return (result);
}

//Una vez tengas el AST y estés en la fase de ejecución, harás algo como:
if (is_builtin(node->args[0]))
    exec_builtin(node->args);
else
    exec_external_command(node->args);

	
int main() //main de prueba para comprobar los builtins
{
}
