/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:37:19 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/02/01 16:21:18 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(int num)
{
	int	sum;

	sum = 0;
	while (num != 0)
	{
		num = num / 10;
		sum++;
	}
	return (sum);
}

static void	ft_write_digit(long num)
{
	char	c;

	if (num >= 10)
	{
		ft_write_digit(num / 10);
		ft_write_digit(num % 10);
	}
	else
	{
		c = num + '0';
		ft_print_char(c);
	}
}

int	ft_print_int(int num)
{
	int		sum;
	long	aux;

	sum = 0;
	aux = (long)num;
	if (aux == 0)
		sum++;
	else if (aux < 0)
	{
		sum++;
		ft_print_char('-');
		aux = aux * -1;
	}
	ft_write_digit(aux);
	sum += count_char(aux);
	return (sum);
}

/*int	main(void)
{
	int	n;

	n = 2147483647;
	printf("\n%d", ft_print_int(n));
	return (0);
}*/
