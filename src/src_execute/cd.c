/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:48:05 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/25 20:12:20 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*char *find_dir(const char *name, t_list **my_env)
{
	t_list *current_env;
	size_t name_len = ft_strlen(name);
	char *var_env;
	
	current_env = my_env;
	while(current_env)
	{
		var_env = (char *)current_env->content;
		if(ft_strncmp(var_env, name, name_len) == 0 && (var_env[name_len] == '=')) //si la variable coincide con la pasada
			return(var_env + name_len + 1); //devuelve el valor	
		current_env = current_env->next;
	}
	return(NULL);
}*/
int builtin_cd(char **args, t_list *my_env)
{
	int i;
	t_list	*env;
	//char *home_dir;
	char *value_var;

	i = 0;
	//home_dir = 
	env = my_env;
	while (env)
	{
		env->content;
		env = env->next;
	}
	if (args[1])
	{
		if(args[1] && args[2])
		{
			printf("cd : too many arguments\n");
			return(1);
		}
		if(args[1][i] == '-')
			//cambia al directorio OLDPWD y mostrarlo
		if(args[1] && (!args[1][i] == '-'))
			//cambiar al directorio en cuestión
	}
	else
	{
		value_var = getenv("HOME");
		printf("valor de home: %s\n", value_var);
	}
	
	
		
}
/*Para que cd funcione correctamente, necesitas tener acceso
a las variables de entorno ya disponibles (como HOME, OLDPWD, PWD)

cd → ir al HOME del usuario (lo obtienes con getenv("HOME"), cd /ruta/absoluta → ir directamente a esa ruta, 
cd ruta/relativa → se interpreta desde el directorio actual, cd - → volver al directorio anterior (usa la variable de entorno OLDPWD), 
cd ~ → equivale a cd $HOME, FUNCIONES: chdir() → cambia el directorio actual, getcwd() → para obtener la ruta actual (puede servir para actualizar PWD), 
setenv() / export (o tus propias funciones) → actualizar PWD y OLDPWD. 

ERRORES COMUNES A CONTROLAR: Ruta inexistente → muestra mensaje tipo cd: no such file or directory, Permisos denegados, 
Demasiados argumentos (cd a b) → debes avisar, Falta de HOME o OLDPWD definidos*/