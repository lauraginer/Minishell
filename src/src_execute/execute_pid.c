/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:15:40 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/25 02:46:41 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int execute_external_command(t_ast_node **args, t_ms **ms, t_list *my_env)
{
	pid_t pid;
	int status;
	char *cmd_path;
	char **argv;
	char **envp;
	
	cmd_path = get_command_path((*args)->args[0], my_env); 
	if (!cmd_path)
	{
		printf("command not found: %s\n", (*args)->args[0]);
		(*ms)->exit_status = 127;
		return (127);
	}
	argv = (*args)->args; //Los argumentos del comando
	envp = NULL; //por ahora NULL
	pid = fork();
	if(pid == 0) //proceso hijo
	{
    	if(execve(cmd_path, argv, envp) == -1) //reemplazas el proceso hijo con el comando execve
		{
			perror("execve"); //si execve falla
    		exit(127);
		}
	}
	else if(pid > 0) //proceso padre
    {
  		waitpid(pid, &status, 0);//espera al proceso hijo y sigue a su ritmo
		if(WIFEXITED(status))
			(*ms)->exit_status = WEXITSTATUS(status);
	}
	else 
	{
		perror("fork");
		(*ms)->exit_status = 1;
	}
	
	free(cmd_path);
	return((*ms)->exit_status);
}

char *manage_relative_or_absolute_path(char *cmd)
{
	if(cmd[0] == '/' || cmd[0] == '.' || ft_strchr(cmd, '/'))
	{
		if(access(cmd, F_OK | X_OK) == 0) //verifica si existe y es ejecutable
			return(ft_strdup(cmd));
		return(NULL);
	}
	return(NULL);
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
	char *path_env;
	char **path_dirs; //subcadenas divididas por el signo ':'
	char *full_path;
	char *temp_path;
	int i;
	
	i = 0;
	full_path = manage_relative_or_absolute_path(cmd);
	if(full_path)
		return(full_path); //comprueba si la ruta es directa
	path_env = get_env_value("PATH", my_env); //obtienes la variable Path del entorno
	if(!path_env)
		return(NULL);
	path_dirs = ft_split(path_env, ':');
	if(!path_dirs)
		return(NULL);
	while(path_dirs[i]) //recorres cada directorio de path
	{
		temp_path = ft_strjoin(path_dirs[i], "/");
		if (!temp_path)
			break;
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path); // Liberar memoria temporal
		if(!full_path)
			break;
		if (access(full_path, F_OK | X_OK) == 0) 
        {
            ft_free_split(path_dirs);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    ft_free_split(path_dirs);
    return (NULL);	
}
//Busca en cada directorio de la variable de entorno PATH si el comando existe allí.

/*añadir nuevas variables o una lista dentro de la lista principal,
fijate en los elementos que tiene añadido pablo en su lista minishell*/

// Ruta absoluta: "/bin/ls" -> devuelve "/bin/ls" (si existe)
// Ruta relativa: "./mi_programa" -> devuelve "./mi_programa" (si existe)
// Comando: "ls" -> busca en PATH y devuelve "/bin/ls" (si se encuentra)
// Comando inexistente: "comando_falso" -> devuelve NULL