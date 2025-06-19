/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:49:30 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/18 17:05:01 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define OK 0
#define ERROR 1

// incluir TOKEN_S_QUOTES en t_token
// para poder identificar que NO tengo que expandir
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
int lexer(t_list *env, char *input)
{
	t_token	*tokens;
	t_token	*node;
	char	*value;
	int		i;
	int		j;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_is_space(input[i]))
			i++;
		if (input[i] == '\"')
		{
			i++;
			j = i;
			while (input[i] != '\"' && input[i] != '\0')
				i++;
			if (input[i] == '\0')
			{
				printf("Syntax error: quotes unclosed");
				return (ERROR);
			}
			else
			{
				value = ft_substr(input, j, i - j);
				node = lstnew_token(value, TOKEN_WORD);
				ft_lstadd_back_token(&tokens, node);
			}
		}
		else if (input[i] == '\'')
		{
			i++;
			j = i;
			while (input[i] != '\'' && input[i] != '\0')
				i++;
			if (input[i] == '\0')
			{
				printf("Syntax error: quotes unclosed");
				return (ERROR);
			}
			else
			{
				value = ft_substr(input, j, i - j);
				node = lstnew_token(value, TOKEN_WORD);//Este sera TOKEN_S_QUOTES
				ft_lstadd_back_token(&tokens, node);
			}
		}
		i++;
	}
}

t_list *copy_env_var(char **envp)
{
	int		i;
	t_list	*new_node;
	t_list	*env;
	char	*copy;

	i = -1;
	env = NULL;
	while (envp[++i])
	{
		copy = ft_strdup(envp[i]);
		if (!copy)
		{
			free_env_list(env);
			return (NULL);
		}
		new_node = ft_lstnew(copy);
		if (!new_node)
		{
			free(copy);
			free_env_list(env);
			return (NULL);
		}
		ft_lstadd_back(&env, new_node);
	}
	return (env);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env;

	env = copy_env_var(envp);
	if (!env)
		exit (1); //crear un enum de errores y meter el correspondiente aqui
	while (argc && argv)
	{
		input = readline("minishell> ");
		if (*input)
			add_history(input);
		else
			break;
		lexer(env, input);
		//free (input);
	}
	free_env_list(env);
}
