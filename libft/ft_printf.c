/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:41:59 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/02/01 16:20:48 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_type(va_list *arg, char pos)
{
	int	size;

	size = 0;
	if (pos == '%')
		size += ft_print_char(pos);
	else if (pos == 'c')
		size += ft_print_char(va_arg(*arg, int));
	else if (pos == 's')
		size += ft_print_string(va_arg(*arg, char *));
	else if (pos == 'p')
		size += ft_print_ptr(va_arg(*arg, void *));
	else if (pos == 'd' || pos == 'i')
		size += ft_print_int(va_arg(*arg, int));
	else if (pos == 'u')
		size += ft_print_unsigint(va_arg(*arg, unsigned int));
	else if (pos == 'x')
		size += ft_print_hexa_lower(va_arg(*arg, unsigned int));
	else if (pos == 'X')
		size += ft_print_hexa_upper(va_arg(*arg, unsigned int));
	return (size);
}

int	ft_printf(char const *str, ...)
{
	int		size;
	int		count;
	va_list	arg;

	size = 0;
	count = 0;
	va_start(arg, str);
	while (str[count])
	{
		if (str[count] == '%')
		{
			size += format_type(&arg, str[count + 1]);
			count++;
		}
		else
		{
			size += ft_print_char(str[count]);
		}
		count++;
	}
	va_end(arg);
	return (size);
}

/*int	main(void)
{
	char c = 'c';
	char str[]= "Hola mundo!";
	int num = 42;

	printf("Imprimir caracter: \n");
	printf("Con printf original: %c\n", c);
	ft_printf("Con mi ft_printf: %c\n", c);
	ft_printf("\n");

	printf("Impfimir string: \n");
	printf("Con printf original: %s\n", str);
	ft_printf("Con mi ft_printf: %s\n", str);
	ft_printf("\n");

	printf("Entero d: \n");
	printf("Printf: %d\n", num);
	ft_printf("Ft_printf: %d\n", num);
	ft_printf("\n");

	printf("Entero i: \n");
	printf("Printf: %i\n", num);
	ft_printf("Ft_printf: %i\n", num);
	ft_printf("\n");

	printf("Entero sin signo: \n");
	printf("Printf: %u\n", num);
	ft_printf("Ft_printf: %u\n", num);
	ft_printf("\n");

	printf("Puntero: \n");
	printf("Printf: %p\n", str);
	ft_printf("Ft_printf: %p\n", str);
	ft_printf("\n");

	printf("Hexadecimal minuscula: \n");
	printf("Printf: %x\n", num);
	ft_printf("Ft_printf: %x\n", num);
	ft_printf("\n");

	printf("Hexadecimal mayuscula: \n");
	printf("Printf: %X\n", num);
	ft_printf("Ft_printf: %X\n", num);
	ft_printf("\n");
}*/
