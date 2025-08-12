
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
		if (ft_strncmp(((char *)ms->my_env->content), "SHLVL=", 6) == 0)
		{
			shlvl = ft_substr(((char *)ms->my_env->content), 6, (ft_strlen(((char *)ms->my_env->content) - 6)));
			lvl = ft_atoi(shlvl);
			lvl++;
			free(shlvl);
			shlvl = ft_itoa(lvl);
			free(ms->my_env->content);
			ms->my_env->content = ft_strjoin("SHLVL=" , shlvl);
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
		if (ft_strncmp(((char *)ms->my_env->content), "SHLVL=", 6) == 0)
		{
			shlvl = ft_substr(((char *)ms->my_env->content), 6, (ft_strlen(((char *)ms->my_env->content) - 6)));
			lvl = ft_atoi(shlvl);
			lvl--;
			free(shlvl);
			shlvl = ft_itoa(lvl);
			free(ms->my_env->content);
			ms->my_env->content = ft_strjoin("SHLVL=" , shlvl);
			free(shlvl);
			break ;
		}
		aux = aux->next;
	}
}
