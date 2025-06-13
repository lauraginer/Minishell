/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:09 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/13 19:30:49 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_echo(char **args);
int builtin_cd(char **args);
int builtin_pwd(char **args);
int builtin_exit(char **args);
int builtin_env(char **envp);
int builtin_export(char **args);
int builtin_unset(char **args);

/*para comprobar si un comando es builtin, Y si lo es, 
ejecútalo directamente sin hacer fork (esto es importante porque algunos built-ins
como cd o exit tienen que afectar directamente al shell, no a un hijo).*/
int is_builtin(char *cmd);

int execute_builtin(char **args)
{
	if(args[0] == 'echo')
		builtin_echo(args);
	if(args[0] == 'cd')
		builtin_cd(args);
	if(args[0] == 'pwd')
		builtin_pwd(args);
	if(args[0] == 'exit')
		builtin_exit(args);
	if(args[0] == 'env')
		builtin_env(args);
	if(args[0] == 'export')
		builtin_export(args);
	if(args[0] == 'unset')
		builtin_unset(args);	
}

//Una vez tengas el AST y estés en la fase de ejecución, harás algo como:
if (is_builtin(node->args[0]))
    exec_builtin(node->args);
else
    exec_external_command(node->args);

	
int main() //main de prueba para comprobar los builtins
{
}
