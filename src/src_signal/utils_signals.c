/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 01:07:08 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/13 12:30:05 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		get_signal = SIGINT;
		if (RL_ISSTATE(RL_STATE_READCMD))
			rl_done = 1;
	}
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
}
