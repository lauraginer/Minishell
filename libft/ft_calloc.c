/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:20:24 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/11 19:24:35 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*point;
	size_t			i;

	i = 0;
	point = malloc(count * size);
	if (!point)
		return (NULL);
	while (i < count * size)
	{
		point[i] = '\0';
		i++;
	}
	return (point);
}
