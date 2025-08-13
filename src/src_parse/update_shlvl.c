/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:30:27 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/08/13 11:30:30 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	increase_shlvl(t_ms *ms)
{
	char	*shlvl;
	int		lvl;
	t_list	*aux;

	if (!ms->my_env)
		return ;
	aux = ms->my_env;
	while (aux)
	{
		if (ft_strncmp(((char *)aux->content), "SHLVL=", 6) == 0)
		{
			shlvl = ft_substr(((char *)aux->content), 6,
					(ft_strlen(((char *)aux->content)) - 6));
			lvl = ft_atoi(shlvl);
			lvl++;
			free(shlvl);
			shlvl = ft_itoa(lvl);
			free(aux->content);
			aux->content = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			break ;
		}
		aux = aux->next;
	}
}

void	decrease_shlvl(t_ms *ms)
{
	char	*shlvl;
	int		lvl;
	t_list	*aux;

	if (!ms->my_env)
		return ;
	aux = ms->my_env;
	while (aux)
	{
		if (ft_strncmp(((char *)aux->content), "SHLVL=", 6) == 0)
		{
			shlvl = ft_substr(((char *)aux->content), 6,
					(ft_strlen(((char *)aux->content)) - 6));
			lvl = ft_atoi(shlvl);
			lvl--;
			free(shlvl);
			shlvl = ft_itoa(lvl);
			free(aux->content);
			aux->content = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			break ;
		}
		aux = aux->next;
	}
}
