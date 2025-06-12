/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:53:55 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/11 19:38:33 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*aux;
	int			end;

	aux = "";
	end = ft_strlen(s);
	c = (char) c;
	while (end >= 0)
	{
		if (c == s[end])
		{
			aux = &s[end];
			return ((char *)aux);
		}
		end--;
	}
	return (NULL);
}
