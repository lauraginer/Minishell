/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:49:30 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/23 17:05:37 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_parse	*init_parse(void)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->tokens = NULL;
	parse->input = NULL;
	parse->i = 0;
	parse->q_flag = 0;
	parse->quot = '.';
	return (parse);
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

void	main_loop(t_parse *parse, t_list *my_env)
{
	while (1)
	{
		parse->input = readline("minishell> ");
		if (!parse->input)
		{
			free_env_list(my_env);
			//free(parse);
			break ;
		}
		if (*(parse->input))
			add_history(parse->input);
		if (lexer(my_env, parse) == FAILURE)
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_parse	*parse;
	t_list	*my_env;

	(void)argc;
	(void)argv;
	my_env = copy_env_var(envp);
	if (!my_env)
		exit (1);
	parse = init_parse();
	if (!parse)
	{
		free_env_list(my_env);
		exit (1);
	}
	main_loop(parse, my_env);
}
