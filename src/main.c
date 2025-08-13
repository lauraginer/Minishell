/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:53:03 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/13 12:11:23 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	get_signal = 0;

void	init_ms(t_ms *ms)
{
	if (ms->f_ast_node)
	{
		free_ast(ms->f_ast_node);
		ms->f_ast_node = NULL;
	}
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

static void	process_input(t_ms *ms)
{
	if (lexer(ms) == FAILURE)
		return ;
	if (syntax_checker(ms) == FAILURE)
		return ;
	expander(ms);
	ms->f_ast_node = ast_main(ms, ms->tokens);
	if (ms->f_ast_node)
	{
		if (process_heredocs(ms->f_ast_node, ms) == 0)
			execute_ast(ms->f_ast_node, ms);
	}
}

void	main_loop(t_ms *ms)
{
	while (1)
	{
		ms->input = readline("minishell> ");
		if (!ms->input)
		{
			decrease_shlvl(ms);
			printf("exit\n");
			free_ms(ms);
		}
		if (*(ms->input))
			add_history(ms->input);
		if (!*(ms->input) || is_empty_line(ms->input))
		{
			free(ms->input);
			ms->input = NULL;
			continue ;
		}
		process_input(ms);
		init_ms(ms);
	}
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
	if (envp && *envp)
	{
		ms->my_env = copy_env_var(envp);
		if (!ms->my_env)
			free_ms(ms);
	}
	increase_shlvl(ms);
	main_loop(ms);
}
