/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:15:40 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/13 11:36:06 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_env_arr(t_ms *ms, t_list *my_env)
{
	char	**envp;
	int		i;
	t_list	*aux;

	i = ft_lstsize(my_env);
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		free_ms(ms);
	aux = my_env;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(((char *)aux->content));
		if (!envp[i])
		{
			free_double_char(envp);
			free_ms(ms);
		}
		aux = aux->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

static int	handle_child_process(char *cmd_path, char **argv, char **envp)
{
	if (execve(cmd_path, argv, envp) == -1)
	{
		perror("execve");
		exit(127);
	}
	return (0);
}

static int	handle_parent_process(pid_t pid, t_ms **ms)
{
	int	status;

	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			(*ms)->exit_status = WEXITSTATUS(status);
	}
	else
	{
		perror("fork");
		(*ms)->exit_status = 1;
	}
	return ((*ms)->exit_status);
}

int	execute_external_command(t_ast_node **args, t_ms **ms, t_list *my_env)
{
	pid_t	pid;
	char	*cmd_path;
	char	**argv;
	char	**envp;

	cmd_path = get_command_path((*args)->args[0], my_env);
	if (!cmd_path)
	{
		printf("command not found: %s\n", (*args)->args[0]);
		(*ms)->exit_status = 127;
		return (127);
	}
	argv = (*args)->args;
	envp = get_env_arr(*ms, my_env);
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd_path, argv, envp);
	handle_parent_process(pid, ms);
	free_double_char(envp);
	free(cmd_path);
	return ((*ms)->exit_status);
}
