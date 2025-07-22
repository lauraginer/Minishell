/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:15:40 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/22 20:16:57 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

execute_external_command(t_ast_node **args, t_ms **ms) //referencia dentro de la estructura a args
{
	t_ast_node *current;
	pid_t pid;
	int status;
	
	current = args;
	pid = fork();
	ms->exit_status = 1;
	if(pid == 0) //proceso hijo
	{
   		//reemplazas el proceso hijo con el comando execve
    	if(execve(cmd_path, current, envp) == -1)
		{
			perror("execve"); //si execve falla
    		ms->exit_status = 127;
			exit(ms->exit_status);
		}
	}
	else if(pid > 0) //proceso padre
    {
  		waitpid(pid, &status, 0);//espera al proceso hijo y sigue a su ritmo
		if(WIFEXITED(status))
			WEXITSTATUS(status) = ms->exit_status;
	}
	else 
		perror("fork");
	printf("el pid en cuestión es: %d\n", pid);
	return(ms->exit_status);
}

char *get_command_path(char *cmd, t_list *my_env) //CMD_PATH
{	
	char *path_dir;
	
	path_dir = getenv("PATH")
	if(!path_dir)
		return(1);
	//if(getcwd(my_env);
}
//Busca en cada directorio de la variable de entorno PATH si el comando existe allí.

/*añadir nuevas variables o una lista dentro de la lista principal,
fijate en los elementos que tiene añadido pablo en su lista minishell*/