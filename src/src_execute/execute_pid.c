/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:15:40 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/21 10:56:09 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

execute_external_command(s_ast_node *args) //referencia dentro de la estructura a args
{
	s_ast_node *current;
	pid_t pid;
	int status;
	
	current = args;
	pid = fork();
	if (pid == 0) // Proceso hijo
	{
   		// Reemplazas el proceso hijo con el comando
    	execve(cmd_path, args, envp);
   		// Si execve falla:
    	perror("execve");
    	exit(127);
	}
	else if (pid < 0)
    	perror("fork");
	else // Proceso padre
	{
  		waitpid(pid, &status, 0);
    	// Aquí puedes guardar el exit_status si quieres
	}
}

char *get_command_path(char *cmd, t_list *my_env); //CMD_PATH
//Busca en cada directorio de la variable de entorno PATH si el comando existe allí.

/*añadir nuevas variables o una lista dentro de la lista principal,
fijate en los elementos que tiene añadido pablo en su lista minishell*/