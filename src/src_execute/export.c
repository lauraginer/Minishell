/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:03:16 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/09 19:04:40 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void print_error_ex(char *arg, t_ms *ms)
{
	printf("export: %s: not a valid identifier\n", arg);
	ms->exit_status = 1;	
}

int is_correct(char *arg) //verifica si es correcto el nombre del env
{
	int i;

	i = 0;
	if(!arg || !*arg)
		return (0);
	if(!ft_isalpha(arg[0]) && arg[0] != '_')
		return(0);
	while(arg[i] && arg[i] != '=') //llega hasta el signo igual para gestionarlo despues
	{
		if(!ft_isalnum(arg[i]) && arg[i] != '_')
			return(0);
		i++;
	}
	return(1);
}

int add_to_env(char *var, t_list **my_env)
{
    t_list *new_node;
    char *new_var;

    new_var = ft_strdup(var); //copia del env que entra
    if(!new_var)
        return(1);
    new_node = ft_lstnew(new_var); //creamos nuevo nodo individual que contiene el puntero a la cadena duplicada
    if(!new_node)
    {
        free(new_var);
        return(1);
    }
    ft_lstadd_back(my_env, new_node); //pasamos el anterior nodo al final de la lista my_env y next apunta a new_node
    return (0);
}

int env_exportable(char *var, t_list **my_env)
{
	t_list *current = *my_env;
	char *env;
	
	while(current)
	{
		env = (char *)current->content;
		if(ft_strcmp(env, var) == 0)
			return (0); //si ya existe la variable, no hacer nada
		current = current->next;
	}
	return(add_to_env(var, my_env)); // Si no está, la añade sin valor
}

int update_env_var(char *var, t_list **my_env) //REAPASA QUE ES UNA LOCURA
{
    char *name;
    char *equal_sign;
    int name_len;
    t_list *current;
    
    equal_sign = ft_strchr(var, '=');
    if (!equal_sign)
        return (0); // No hay '=', no es una variable para actualizar
    
    name_len = equal_sign - var;
    name = ft_substr(var, 0, name_len);
    if (!name)
        return (1); // Error de memoria
    
    current = *my_env; // Desreferenciar el puntero doble
    while (current)
    {
        char *env_entry = (char *)current->content;
        if (ft_strncmp(env_entry, name, name_len) == 0 && 
            (env_entry[name_len] == '=' || env_entry[name_len] == '\0'))
        {
            // Reemplazar la variable existente
            free(current->content);
            current->content = ft_strdup(var);
            free(name);
            return (current->content ? 0 : 1); // Verificar si ft_strdup tuvo éxito
        }
        current = current->next;
    }
    free(name);
    return (add_to_env(var, my_env)); // Añadir nueva variable
}

int builtin_export(char **args, t_list *my_env, t_ms *ms)
{
	t_list *current_env;
	int i;

	current_env = my_env;
	i = 1;
	ms->exit_status = 0;
	if(!args[1])
	{
		while(current_env)
		{
			printf("declare -x %s\n", (char *)current_env->content);
			current_env = current_env->next;
		}
		return (0);
	}
	while(args[i])//leemos cada argumento porque no existe un limite válido
	{
		if(!is_correct(args[i]))
			print_error_ex(args[i], ms);
		else if(ft_strchr(args[i], '=')) //busca en cualquier pos
		{
			if (update_env_var(args[i], &my_env) != 0)
			{
				ms->exit_status = 1;
				printf("export: error: could not allocate memory\n");
			}
		}
		else
		{
			if (env_exportable(args[i], &my_env) != 0) //gestiona sin signo
			{
				ms->exit_status = 1;
				printf("export: error: could not allocate memory\n");
			}
		}
		i++;
	}
	return(ms->exit_status);
}
