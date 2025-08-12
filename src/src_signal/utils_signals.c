/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 01:07:08 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/12 13:59:35 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		get_signal = SIGINT;
	
		if (RL_ISSTATE(RL_STATE_READCMD)) // Solo interrumpir readline si está activo
			rl_done = 1;
	}
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;
	
	sa_int.sa_handler = &heredoc_signal_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0; // SIN SA_RESTART para que readline falle
	sigaction(SIGINT, &sa_int, NULL);
}
