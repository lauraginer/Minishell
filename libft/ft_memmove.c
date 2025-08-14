/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:29:26 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/04/20 11:56:22 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	count;

	count = 0;
	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		while (count < n)
		{
			((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
			count++;
		}
	}
	else
	{
		while (n > 0)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
			n--;
		}
	}
	return (dest);
}

/*int	main(void)
{
	char src[]= "hola";
	char dest[20];

	ft_memmove(dest,src,30);
	printf("%s", dest);
}*/
