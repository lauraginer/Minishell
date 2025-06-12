/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:01:03 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/19 18:05:24 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len > s_len - start)
		len = s_len - start;
	if (start >= s_len)
		return (ft_strdup(""));
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = start;
	while (i < start + len)
	{
		p[i - start] = s[i];
		i++;
	}
	p[i - start] = '\0';
	return (p);
}

/*int main()
{
	printf("%s",ft_substr("",5,10));
}*/
