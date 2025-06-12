/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:58:02 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/11 19:35:30 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*point;
	size_t	i;

	i = 0;
	point = malloc(ft_strlen(s1) + 1);
	if (!point)
		return (NULL);
	while (s1[i])
	{
		point[i] = s1[i];
		i++;
	}
	point[i] = '\0';
	return (point);
}
