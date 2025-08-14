/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:10:31 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/11 19:26:41 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_digit(int n, int fd)
{
	char	a;

	if (n < 0)
	{
		a = '0' - n;
	}
	else
	{
		a = n + '0';
	}
	write(fd, &a, 1);
}

static void	get_digit(int n, int fd)
{
	if (n <= 9 && n >= -9)
	{
		write_digit(n, fd);
	}
	else
	{
		get_digit((n / 10), fd);
		write_digit((n % 10), fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
	}
	get_digit(n, fd);
}
