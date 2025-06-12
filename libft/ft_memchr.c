/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:10:31 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/11 19:26:49 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*aux;
	size_t			i;

	i = 0;
	aux = (unsigned char *)s;
	while (i < n)
	{
		if ((unsigned char)c == aux[i])
		{
			return ((void *)&aux[i]);
		}
		i++;
	}
	return (NULL);
}
