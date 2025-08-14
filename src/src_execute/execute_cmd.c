/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:15:40 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/14 19:37:31 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	check_empty_command(t_ast_node **args, t_ms **ms)
{
	if (!(*args)->args[0] || (*args)->args[0][0] == '\0')
	{
		(*ms)->exit_status = 0;
		return (1);
	}
	return (0);
}

static int	handle_command_error(t_ast_node **args, t_ms **ms)
{
	if (errno == EACCES)
	{
		fprintf(stderr, "%s: Permission denied\n", (*args)->args[0]);
		(*ms)->exit_status = 126;
		return (126);
	}
	else if (errno == EISDIR)
	{
		fprintf(stderr, "%s: Is a directory\n", (*args)->args[0]);
		(*ms)->exit_status = 126;
		return (126);
	}
	else
	{
		printf("command not found: %s\n", (*args)->args[0]);
		(*ms)->exit_status = 127;
		return (127);
	}
}

int	execute_external_command(t_ast_node **args, t_ms **ms, t_list *my_env)
{
	pid_t	pid;
	char	*cmd_path;
	char	**argv;
	char	**envp;

	if (check_empty_command(args, ms))
		return (0);
	cmd_path = get_command_path((*args)->args[0], my_env);
	if (!cmd_path)
		return (handle_command_error(args, ms));
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
