/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:49:30 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/19 12:44:55 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// incluir TOKEN_S_QUOTES en t_token
// para poder identificar qué NO tengo que expandir
/*Lo de los espacios es un follon
	Ejemplos:
	* echo hola adios --> hola adios
	* echo hola $USER --> hola user_name
	* echo hola$USER --> holauser_name
	
	En este ultimo caso: si separo los tokens tendria
	un WORD hola y un EXPAND $USER, ¿ PERO COMO SE CUANDO
	HABIA UN ESPACIO Y CUANDO NO?
	Voy a eliminar el TOKEN_EXPAND y en la fase de expansion
	recorro todos los tokens y expando cuando me encuentre 
	un $, excepto el TOKEN_S_QUOTES. 
	No olvidar que $? se expande en la ejecucion	
	
	*/



t_parse *init_parse()
{
	t_parse *parse;
	
	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->tokens = NULL;
	parse->input = NULL;
	parse->count = 0;
}

t_list *copy_env_var(char **envp)
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
		if (parse->input && *(parse->input))
			add_history(parse->input);
		else
			break;
		if (lexer(my_env, parse) == FAILURE)
			continue;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_parse	*parse;
	t_list	*my_env;

	(void)argc;
	(void)argv;
	my_env = copy_env_var(envp);
	if (!my_env)
		exit (1); //crear un enum de errores y meter el correspondiente aqui
	parse = init_parse();
	if (!parse)
	{
		free_env_list(my_env);
		exit (1);
	}	
	main_loop(parse, my_env);
}
