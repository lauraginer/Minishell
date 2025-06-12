/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:33:19 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/05 19:46:39 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>

/*void test_func(unsigned int index, char *c)
{
	if (index % 2 == 0)
        *c = toupper(*c);
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/*int main(void)
{
	char	*s;
	char *s_copy;
	s = "holaaaaaa";
	s_copy = ft_strdup(s);
	ft_striteri(s_copy, test_func);
	printf("%s",s_copy);
	return (0);
}*/
