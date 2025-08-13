/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:09 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/13 11:08:12 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	needs_parent_execution(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_ast_node *node, t_ms *ms)
{
	int	result;

	result = 0;
	if (ft_strncmp(node->args[0], "echo", 5) == 0)
		result = builtin_echo(node->args, ms);
	else if (ft_strncmp(node->args[0], "cd", 3) == 0)
		result = builtin_cd(node->args, ms);
	else if (ft_strncmp(node->args[0], "pwd", 4) == 0)
		result = builtin_pwd(node->args, ms);
	else if (ft_strncmp(node->args[0], "exit", 5) == 0)
		result = builtin_exit(node->args, ms);
	else if (ft_strncmp(node->args[0], "env", 4) == 0)
		result = builtin_env(node->args, ms->my_env, ms);
	else if (ft_strncmp(node->args[0], "export", 7) == 0)
		result = builtin_export(node->args, &ms->my_env, ms);
	else if (ft_strncmp(node->args[0], "unset", 6) == 0)
		result = builtin_unset(node->args, &ms->my_env, ms);
	ms->exit_status = result;
	return (result);
}

int	execute_builtin_with_fork(t_ast_node *node, t_ms *ms)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execute_builtin(node, ms);
		exit(ms->exit_status);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ms->exit_status = WEXITSTATUS(status);
		return (ms->exit_status);
	}
	else
	{
		perror("fork");
		ms->exit_status = 1;
		return (ms->exit_status);
	}
}
