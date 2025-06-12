/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:34:48 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/04/22 16:28:26 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	aux;

	i = 0;
	aux = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] && len >= (size_t)ft_strlen(needle))
	{
		j = 0;
		i = aux;
		while (needle[j])
		{
			if (needle[j] != haystack[i])
				break ;
			j++;
			i++;
		}
		if (needle[j] == '\0')
			return (&((char *)haystack)[aux]);
		aux++;
		len --;
	}
	return (NULL);
}
