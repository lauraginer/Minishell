/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:48:05 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/12 21:16:59 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int error_exit_status(t_ms *ms)
{
	ms->exit_status = 1;
	return (1);
}
int	special_case(char *str)
{
	const char	*target_dir;
	char		old_dir[PATH_MAX];

	if ((ft_strncmp(str, "--", 3) == 0) || ft_strncmp(str, "~", 2) == 0)
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
	return (-1);
}

int	handle_cd_home(t_ms *ms)
{
	const char	*target_dir;
	char		old_dir[PATH_MAX];

	target_dir = getenv("HOME");
	if (!target_dir)
	{
		printf("cd: HOME not set\n");
		return (error_exit_status(ms));
	}
	if (getcwd(old_dir, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (error_exit_status(ms));
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (error_exit_status(ms));
	}
	update_pwd_env(old_dir);
	ms->exit_status = 0;
	return (0);
}

int	handle_cd_oldpwd(t_ms *ms)
{
	const char	*target_dir;
	char		old_dir[PATH_MAX];

	target_dir = getenv("OLDPWD");
	if (!target_dir)
	{
		printf("cd: OLDPWD not set\n");
		return (error_exit_status(ms));
	}
	if (getcwd(old_dir, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (error_exit_status(ms));
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (error_exit_status(ms));
	}
	printf("%s\n", target_dir);
	update_pwd_env(old_dir);
	ms->exit_status = 0;
	return (0);
}

int	handle_cd_path(char *path, t_ms *ms)
{
	char	old_dir[PATH_MAX];

	if (getcwd(old_dir, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (error_exit_status(ms));
	}
	if (chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", path);
		return (error_exit_status(ms));
	}
	update_pwd_env(old_dir);
	ms->exit_status = 0;
	return (0);
}

int	builtin_cd(char **args, t_ms *ms)
{
	int	flag;

	if (!args)
		return (error_exit_status(ms));
	if (!args[1])
		return (handle_cd_home(ms));
	if (args[2])
	{
		printf("cd: too many arguments\n");
		return (error_exit_status(ms));
	}
	if (args[1][0] == '-' && !args[1][1])
		return (handle_cd_oldpwd(ms));
	flag = special_case(args[1]);
	if (flag != -1)
	{
		ms->exit_status = flag;
		return (flag);
	}
	return (handle_cd_path(args[1], ms));
}
