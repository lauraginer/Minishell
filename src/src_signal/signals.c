
#include "../../inc/minishell.h"

void	signal_handler(int sig)
{  
	get_signal = sig;
	signal_logic();
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = &signal_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART | SA_NODEFER;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	signal_logic(void)
{
	if (get_signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	get_signal = 0;
}

void	heredoc_signal_handler(int sig)
{
	get_signal = sig;
	// No llamar signal_logic() aquí para heredoc
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;
	
	sa_int.sa_handler = &heredoc_signal_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0; // SIN SA_RESTART para que readline falle
	sigaction(SIGINT, &sa_int, NULL);
}

void	restore_signals(void)
{
	setup_signals(); // Restaurar configuración normal
}
