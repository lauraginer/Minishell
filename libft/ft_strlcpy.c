/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:31:43 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/04/20 13:16:29 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_size;
	size_t	i;

	src_size = 0;
	i = 0;
	while (src[src_size])
		src_size++;
	while (src[i] != '\0' && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (src_size);
}

/*int	main(void)
{
	char src[]="";
	char dst[]= "Adios";
	size_t	x;

	x = ft_strlcpy(dst, src, 2);
	printf("%s   %ld", dst, x);
}*/