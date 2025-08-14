/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:40:21 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/03 09:12:59 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(char *s, int n, int size)
{
	int	i;

	i = 0;
	s[i] = '0';
	if (n < 0)
	{
		s[i] = '-';
		i++;
	}
	while (size - 1 >= i)
	{
		if (n < 0)
		{
			s[size - 1] = -(n % 10) + '0';
		}
		else
		{
			s[size - 1] = n % 10 + '0';
		}
		n = n / 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	int		str_size;
	char	*str;
	int		nbr;

	nbr = n;
	str_size = 0;
	if (nbr < 0)
		str_size++;
	if (nbr == 0)
		str_size++;
	while (nbr != 0)
	{
		str_size++;
		nbr = nbr / 10;
	}
	str = malloc(sizeof(char) * (str_size + 1));
	if (!str)
		return (NULL);
	ft_putnbr(str, n, str_size);
	str[str_size] = '\0';
	return (str);
}
