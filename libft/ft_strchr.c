/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:33:03 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/11 19:33:17 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*str_occur;
	int			i;

	str_occur = "";
	i = 0;
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
		{
			str_occur = &s[i];
			return ((char *)str_occur);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		str_occur = &s[i];
		return ((char *)str_occur);
	}
	return (NULL);
}
