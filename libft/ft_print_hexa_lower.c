/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa_lower.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:09:20 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/02/01 16:21:33 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(unsigned int value)
{
	int	sum;

	sum = 0;
	while (value != 0)
	{
		value = value / 16;
		sum++;
	}
	return (sum);
}

static void	ft_conv_hexa(unsigned int value)
{
	char	*base;

	base = "0123456789abcdef";
	if (value >= 16)
	{
		ft_conv_hexa(value / 16);
		ft_conv_hexa(value % 16);
	}
	else
	{
		ft_print_char(base[value]);
	}
}

int	ft_print_hexa_lower(unsigned int num)
{
	int	size;

	size = 0;
	if (num == 0)
		size += ft_print_char('0');
	else
	{
		ft_conv_hexa(num);
		size += count_char(num);
	}
	return (size);
}

/*int	main(void)
{
	unsigned int x;

	x = 4294967295;
	printf("\n%d",ft_print_hexa_lower(x));
}*/