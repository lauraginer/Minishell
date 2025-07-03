

#include "../inc/minishell.h"

t_ms	*init_ms(void)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	if (!ms)
		return (NULL);
	ms->tokens = NULL;
	ms->input = NULL;
	ms->sub_tokens = NULL;
	ms->i = 0;
	ms->exp_f = 0;
	ms->s_quot = 0;
	ms->quot = '.';
	return (ms);
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
		{
			free_ms(ms);
			//free(ms);
			//break ;
		}
		if (*(ms->input))
			add_history(ms->input);
		if (lexer(ms) == FAILURE)
			continue ;
		expander(ms);
		
		ms = init_ms();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	(void)argc;
	(void)argv;
	ms = init_ms();
	ms->exit_status = 0;
	if (!ms)
		exit (1);
	ms->my_env = copy_env_var(envp);
	if (!ms->my_env)
		free_ms(ms);
	main_loop(ms);
}
