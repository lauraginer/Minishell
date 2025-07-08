
#include "../../inc/minishell.h"

char	*replace_env(t_ms *ms, t_list *tmp, char **word) //poner **word en .h
{
	int	i;
	int	j;

	i = 0;
	free (*word);
	while (((char *)tmp->content)[i])
	{
		if (((char *)tmp->content)[i] == '=')
			break ;
		i++;
	}
	i++;
	j = i;
	while (((char *)tmp->content)[i])
		i++;
	*word = malloc(sizeof(char) * (i - j + 1));
	if (!(*word))
		free_ms(ms);
	i = 0;
	while (((char *)tmp->content)[j])
		(*word)[i++] = ((char *)tmp->content)[j++];
	(*word)[i] = '\0';
	return (*word);
}

void	check_env_split(t_ms *ms, t_token *aux_t, int *count)
{
	char	*word;
	int		i;
	int		len;
	t_list	*tmp;

	tmp = ms->my_env;
	i = ms->i;
	while (ft_isalnum(aux_t->value[ms->i]) || aux_t->value[ms->i] == '_')
		ms->i++;
	word = ft_substr(aux_t->value, i, ms->i - i);
	if (!word)
		free_ms(ms);
	while (tmp)
	{
		len = 0;
		while (((char *)tmp->content)[len] != '=')
			len++;
		if (ft_strlen(word) > len)
			len = ft_strlen(word);
		if (ft_strncmp(word, (char *)tmp->content, len) == 0)
			ms->sub_tokens[*count] = replace_env(ms, tmp, &word);
		tmp = tmp->next;
	}
	check_env_split2(ms, count, word);
}

void	check_env_split2(t_ms *ms, int *count, char *word) // INCLUIR **word en el prototipo del .h
{
	if (!ms->sub_tokens[*count])
	{
		free (word);
		ms->sub_tokens[*count] = ft_strdup("");
		if (!ms->sub_tokens[*count])
			free_ms(ms);
	}
	(*count)++;
}
