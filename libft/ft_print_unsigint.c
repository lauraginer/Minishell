/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:39:14 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/02/01 16:20:57 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(unsigned int num)
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

static void	ft_write_digit(unsigned int num)
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

int	ft_print_unsigint(unsigned int num)
{
	int	sum;

	sum = 0;
	if (num == 0)
	{
		sum++;
		ft_print_char('0');
	}
	else
	{
		ft_write_digit(num);
		sum += count_char(num);
	}
	return (sum);
}
/*int	main(void)
{
	unsigned int	n;

	n = 4294967295;
	printf("\n%d", ft_print_unsigint(n));
	return (0);
}*/