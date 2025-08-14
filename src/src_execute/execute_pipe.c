/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/13 11:23:07 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execute_left_child(int *pipe_fd, t_ast_node *pipe_node, t_ms *ms)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_ast(pipe_node->left, ms);
	exit(ms->exit_status);
}

static void	execute_right_child(int *pipe_fd, t_ast_node *pipe_node, t_ms *ms)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_ast(pipe_node->right, ms);
	exit(ms->exit_status);
}

static int	wait_children(pid_t left_pid, pid_t right_pid, t_ms *ms)
{
	int	status;

	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
	ms->exit_status = WEXITSTATUS(status);
	return (ms->exit_status);
}

int	execute_pipe(t_ast_node *pipe_node, t_ms *ms)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	ms->exit_status = 0;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		ms->exit_status = 1;
		exit(ms->exit_status);
	}
	left_pid = fork();
	if (left_pid == 0)
		execute_left_child(pipe_fd, pipe_node, ms);
	right_pid = fork();
	if (right_pid == 0)
		execute_right_child(pipe_fd, pipe_node, ms);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (wait_children(left_pid, right_pid, ms));
}
