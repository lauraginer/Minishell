/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:48:05 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/04 23:10:51 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int update_pwd_env(const char *old_dir)
{
	char current_dir[PATH_MAX];
	
	if (getcwd(current_dir, PATH_MAX) == NULL) //obtenemos el directorio actual después del cambio
	{
		perror("getcwd");
		return (1);
	}
	if (setenv("OLDPWD", old_dir, 1) != 0) //actualizamos las variables de entorno
	{
		perror("setenv OLDPWD");
		return (1);
	}
	if (setenv("PWD", current_dir, 1) != 0)
	{
		perror("setenv PWD");
		return (1);
	}
	return (0);
}

int special_case(char *str)
{
	const char *target_dir;
	char old_dir[PATH_MAX];

	if (!str)
		return (-1);
	if (ft_strncmp(str, "--", 3) == 0 || ft_strncmp(str, "~", 2) == 0)
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if (getcwd(old_dir, PATH_MAX) == NULL)
		{
			perror("getcwd");
			return (1);
		}
		
		if (chdir(target_dir) != 0)
		{
			perror("cd");
			return (1);
		}
		update_pwd_env(old_dir);
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
	int flag;
	const char *target_dir; //guarda la ruta de destino a la que queremos cambiar
	char old_dir[PATH_MAX]; //guarda la ruta completa del directorio actual antes de cambiar, para OLDPWD
	
	if (!args) //solo hace falta para la prueba, cuando tengas la funcion principal QUITALO
		return (1);
	if (!args[1])
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if (getcwd(old_dir, PATH_MAX) == NULL)//guardamos el directorio actual antes de cambiarlo
		{
			perror("getcwd");
			return (1);
		}
		if (chdir(target_dir) != 0)
		{
			perror("cd");
			return (1);
		}
		update_pwd_env(old_dir);//actualizamos las variables de entorno
		return (0);
	}
	if (args[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (args[1][0] == '-' && !args[1][1])
	{
		target_dir = getenv("OLDPWD");
		if (!target_dir)
		{
			printf("cd: OLDPWD not set\n");
			return (1);
		}
		if (getcwd(old_dir, PATH_MAX) == NULL)//guardamos el directorio actual antes de cambiarlo
		{
			perror("getcwd");
			return (1);
		}
		if (chdir(target_dir) != 0)
		{
			perror("cd");
			return (1);
		}
		printf("%s\n", target_dir);
		update_pwd_env(old_dir);//actualizamos las variables de entorno
		return (0);
	}
	flag = special_case(args[1]);
	if (flag != -1)
		return flag;	
	//Manejar rutas normales
	if (getcwd(old_dir, PATH_MAX) == NULL) //guardamos el directorio actual antes de cambiarlo
	{
		perror("getcwd");
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		printf("cd: %s: No such file or directory\n", args[1]);
		return (1);
	}
	update_pwd_env(old_dir); //actualizamos las variables de entorno
	return (0);
}
