/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:48:05 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/27 21:07:55 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int special_case(char *str)
{
	const char *target_dir;

	if (ft_strncmp(str, "--", 3) == 0)
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if (chdir(target_dir) != 0)
		{
			perror("cd");
			return (1);
		}
		return (0);
	}
	else if (str[0] == '-' && str[1] == '-' && str[2])
	{
		printf("cd: -%c: invalid option\n", str[2]);
		return (1);
	}
	return (-1); //-1 si no es un caso especial
}

int builtin_cd(char **args)
{
	int i;
	int flag;
	const char *target_dir; //guarda la ruta de destino a la que queremos cambiar
	char current_dir[PATH_MAX]; //guarda la ruta completa del directorio actual despues de cambiar, PWD
	char old_dir[PATH_MAX]; //guarda la ruta completa del directorio actual antes de cambiar, OLDPWD
	
	flag = special_case(args[1]);
	if (args[1])
	{
		if (args[1] && args[2])
		{
			printf("cd: too many arguments\n");
			return (1);
		}
		if (flag != -1)
				return flag;
		if (args[1][0] == '-')
		{
			target_dir = getenv("OLDPWD");
			if (!target_dir)
			{
				printf("cd: OLDPWD not set\n");
				return (1);
			}
			if (chdir(target_dir) != 0)
			{
				perror("cd");
				return (1);
			}
			printf("%s\n", target_dir);
			return (0);
		}
		if (chdir(args[1]) != 0) // si otro directorio especifico no existe
		{
			printf("cd: %s: No such file or directory\n", args[1]);
			return (1);
		}
		return (0);
	}
	else
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if (chdir(target_dir) != 0)
		{
			perror("cd");
			return (1);
		}
		
	}
	return (0);
}
/*Para que cd funcione correctamente, necesitas tener acceso
a las variables de entorno ya disponibles (como HOME, OLDPWD, PWD)

cd → ir al HOME del usuario (lo obtienes con getenv("HOME"), cd /ruta/absoluta → ir directamente a esa ruta, 
cd ruta/relativa → se interpreta desde el directorio actual, cd - → volver al directorio anterior (usa la variable de entorno OLDPWD), 
cd ~ → equivale a cd $HOME, FUNCIONES: chdir() → cambia el directorio actual, getcwd() → para obtener la ruta actual (puede servir para actualizar PWD), 
setenv() / export (o tus propias funciones) → actualizar PWD y OLDPWD. 

ERRORES COMUNES A CONTROLAR: Ruta inexistente → muestra mensaje tipo cd: no such file or directory, Permisos denegados, 
Demasiados argumentos (cd a b) → debes avisar, Falta de HOME o OLDPWD definidos*/

