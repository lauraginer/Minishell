/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:15:40 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/23 20:38:04 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int execute_external_command(t_ast_node **args, t_ms **ms, t_list *my_env) //referencia dentro de la estructura a args
{
	t_ast_node *current;
	pid_t pid;
	int status;
	char *cmd_path;
	t_list *envs;
	
	current = args;
	envs = my_env;
	pid = fork();
	cmd_path = get_command_path(args->args, envs);
	ms->exit_status = 1;
	if(pid == 0) //proceso hijo
	{
    	if(execve(cmd_path, current, envp) == -1) //reemplazas el proceso hijo con el comando execve
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

char manage_relative_or_absolute_path(char *cmd)
{
	if(cmd[0] == '/' || cmd[0] == '.' || ft_strchr(cdm, '/'))
	{
		if(access(cmd, F_OK | X_OK) == 0) //verifica si existe y es ejecutable
			return(ft_strdup(cmd));
		return(NULL);
	}
}

char *get_env_value(char *name, t_list *my_env)
{
	t_list	*current;
	size_t len;
	
	current = my_env;
	len = ft_strlen(name);
	while(current)
	{
		if(ft_strncmp(current->content, name, len) == 0 && ((char *)current->content)[len] == '=')
            return (((char *)current->content) + len + 1);
		current = current->next;
	}
	return(NULL);
}
char *get_command_path(char *cmd, t_list *my_env) //CMD_PATH
{	
	char *path_dir;
	char **subpaths; //subcadenas divididas por el signo ':'
	char *full_path;
	
	full_path = manage_relative_or_absolute_path(cmd);
	if(full_path)
		return(full_path); //comprueba si la ruta es directa
	path_dir = get_env_value("PATH", my_env) //obtienes la variable Path del entorno
	if(!path_dir)
		return(NULL);
	subpaths = ft_split(path_dir, ':');
	if(!subpaths)
		return(NULL);
	
	
}
//Busca en cada directorio de la variable de entorno PATH si el comando existe allí.

/*añadir nuevas variables o una lista dentro de la lista principal,
fijate en los elementos que tiene añadido pablo en su lista minishell*/

// Ruta absoluta: "/bin/ls" -> devuelve "/bin/ls" (si existe)
// Ruta relativa: "./mi_programa" -> devuelve "./mi_programa" (si existe)
// Comando: "ls" -> busca en PATH y devuelve "/bin/ls" (si se encuentra)
// Comando inexistente: "comando_falso" -> devuelve NULL