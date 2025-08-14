/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 09:26:22 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/19 18:03:40 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_counter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*fill_word(char const *s, char c, int i)
{
	char	*word;
	int		count;
	int		aux;

	count = 0;
	aux = i;
	while (s[i] != c && s[i] != '\0')
	{
		count++;
		i++;
	}
	word = malloc(sizeof(char) * (count + 1));
	count = 0;
	while (s[aux] != c && s[aux] != '\0')
	{
		word[count] = s[aux];
		aux++;
		count++;
	}
	word[count] = '\0';
	return (word);
}

static void	*free_array(char **res, int cont)
{
	int	i;

	i = 0;
	while (i < cont)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (words_counter(s, c) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			res[j] = fill_word(s, c, i);
			if (!res[j])
				return (free_array(res, j));
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	res[j] = 0;
	return (res);
}
