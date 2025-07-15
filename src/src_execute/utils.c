/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:28:39 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/15 17:30:34 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
int update_env_var(char *var, t_list **my_env) //REPASA QUE ES UN POCO LOCURA
{
    char *name;
    char *equal_sign;
    int name_len;
    t_list *current;
    
    equal_sign = ft_strchr(var, '=');
    if(!equal_sign)
        return (0); //No hay '=', no es una variable para actualizar
    name_len = equal_sign - var;
    name = ft_substr(var, 0, name_len);
    if(!name)
        return (1); // Error de memoria
    current = *my_env; // Desreferenciar el puntero doble
    while(current)
    {
        char *env_entry = (char *)current->content;
        if(ft_strncmp(env_entry, name, name_len) == 0 && 
            (env_entry[name_len] == '=' || env_entry[name_len] == '\0'))//reemplazar la variable existente
        {
            free(current->content);
            current->content = ft_strdup(var);
            free(name);
            return (current->content ? 0 : 1); //verificar si ft_strdup tuvo éxito
        }
        current = current->next;
    }
    free(name);
    return (add_to_env(var, my_env)); //añadir nueva variable
}

void print_env(t_list **my_env)
{
	t_list *current_env;
	char *env_var;
	char *equal_pos;
	
	current_env = *my_env;
	while(current_env)
	{
		env_var = (char *)current_env->content;
		equal_pos = ft_strchr(env_var, '=');
		
		if(equal_pos)//si tiene el signo igual de los cojones
		{
			*equal_pos = '\0'; //cambiamos el igual por el nulo PORQUE no funciona si no se toca la cadena original, asi que parten en dos
			printf("declare -x %s=\"%s\"\n", env_var, equal_pos + 1);
			*equal_pos = '=';
		}
		else
			printf("declare -x %s\n", env_var);
		current_env = current_env->next;
	}
	return ;
}
