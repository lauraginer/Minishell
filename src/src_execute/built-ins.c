/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:09 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/15 17:58:54 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int builtin_cd(char **args, t_ms *ms);
int builtin_pwd(char **args, t_ms *ms);
int builtin_exit(char **args, t_ms *ms);
int builtin_env(char **args, t_list *my_env, t_ms *ms);
int builtin_export(char **args, t_list *my_env, t_ms *ms);
int builtin_unset(char **args, t_list **my_env, t_ms *ms);

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
		result = builtin_pwd(args, ms);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		result = builtin_exit(args, ms);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		result = builtin_env(args, ms->my_env, ms);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		result = builtin_export(args, ms->my_env, ms);
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
