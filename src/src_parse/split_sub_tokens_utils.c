/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sub_tokens_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:29:39 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/08/14 17:56:12 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*replace_env(t_ms *ms, t_list *tmp, char **word)
{
	int	i;
	int	j;

	i = 0;
	free (*word);
	while (((char *)tmp->content)[i] && ((char *)tmp->content)[i] != '=')
		i++;
	if (((char *)tmp->content)[i] == '\0')
	{
		*word = ft_strdup("");
		if (!(*word))
			free_ms(ms);
		return (*word);
	}
	j = ++i;
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
	t_checkenv	*check;
	int			i;

	check = ft_calloc(sizeof(t_checkenv), 1);
	if (!check)
		free_ms(ms);
	check->tmp = ms->my_env;
	check->len = 0;
	i = ms->i;
	while (ft_isalnum(aux_t->value[ms->i]) || aux_t->value[ms->i] == '_')
		ms->i++;
	check->word = ft_substr(aux_t->value, i, ms->i - i);
	if (!check->word)
		free_ms(ms);
	check_env_split2(ms, count, &check);
	if (check)
		free(check);
}

void	check_env_split2(t_ms *ms, int *count, t_checkenv **check)
{
	while ((*check)->tmp)
	{
		(*check)->len = 0;
		while (((char *)(*check)->tmp->content)[(*check)->len] &&
			((char *)(*check)->tmp->content)[(*check)->len] != '=')
			(*check)->len++;
		if (ft_strlen((*check)->word) > (*check)->len)
			(*check)->len = ft_strlen((*check)->word);
		if (ft_strncmp((*check)->word,
				(char *)(*check)->tmp->content, (*check)->len) == 0
			&& (((char *)(*check)->tmp->content)[(*check)->len] == '='
			|| ((char *)(*check)->tmp->content)[(*check)->len] == '\0'))
			ms->sub_tokens[*count] = replace_env(ms, (*check)->tmp, &(*check)->word);
		(*check)->tmp = (*check)->tmp->next;
	}
	if (!ms->sub_tokens[*count])
	{
		free((*check)->word);
		free((*check));
		*check = NULL;
		ms->sub_tokens[*count] = ft_strdup("");
		if (!ms->sub_tokens[*count])
			free_ms(ms);
	}
	(*count)++;
}
