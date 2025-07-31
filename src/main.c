#include "../inc/minishell.h"

volatile sig_atomic_t get_signal = 0;

void	init_ms(t_ms *ms)
{
	ms->tokens = NULL;
	ms->input = NULL;
	ms->sub_tokens = NULL;
	ms->i = 0;
	ms->exp_f = 0;
	ms->s_quot = 0;
	ms->redir_f = 0;
	ms->quot = '.';
}

t_list	*copy_env_var(char **envp)
{
	int		i;
	t_list	*new_node;
	t_list	*my_env;
	char	*copy;

	i = -1;
	my_env = NULL;
	while (envp[++i])
	{
		copy = ft_strdup(envp[i]);
		if (!copy)
		{
			free_env_list(my_env);
			return (NULL);
		}
		new_node = ft_lstnew(copy);
		if (!new_node)
		{
			free(copy);
			free_env_list(my_env);
			return (NULL);
		}
		ft_lstadd_back(&my_env, new_node);
	}
	return (my_env);
}

void	main_loop(t_ms *ms)
{
	while (1)
	{
		ms->input = readline("minishell> ");
		if (!ms->input)
			free_ms(ms);
		if (*(ms->input))
			add_history(ms->input);
		if (lexer(ms) == FAILURE)
			continue ;
		if (syntax_checker(ms) == FAILURE)
			continue ;
		expander(ms);
		// Ejecutor temporal para comandos simples (sin pipes)
		//execute_simple_tokens(ms);
		//implementar ast_pipe cuando el parser esté listo
		ms->f_ast_node = ast_main(ms, ms->tokens);
		debug_ast(ms->f_ast_node);
		//ms->f_ast_node = NULL; // Temporal hasta implementar parser
		init_ms(ms);
	}
	/*hay un monton de still reachable de valgrind que son mios al hacer CTRL + C,
	habra que meterlo en el manejo de señales*/
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	(void)argc;
	(void)argv;
	setup_signals();
	ms = ft_calloc(1, sizeof(t_ms));
	init_ms(ms);
	ms->exit_status = 0;
	if (!ms)
		exit (1);
	ms->my_env = copy_env_var(envp);
	if (!ms->my_env)
		free_ms(ms);
	main_loop(ms);
}
