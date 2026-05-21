/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:07:06 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:25:57 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

void	ft_putchar(int c, int *data)
{
	if (*data != -1)
	{
		if (write(1, &c, 1) == -1)
			*data = -1;
		else
			*data += 1;
	}
}

void	ft_putstr(char *str, int *data)
{
	if (!str)
		ft_putstr("(null)", data);
	else
	{
		while (*str)
		{
			ft_putchar(*str, data);
			str++;
		}
	}
}

void	ft_formats(const char *format, va_list ap, int *data)
{
	if (*format == '%')
		ft_putchar('%', data);
	else if (*format == 'c')
		ft_putchar(va_arg(ap, int), data);
	else if (*format == 's')
		ft_putstr(va_arg(ap, char *), data);
	else if (*format == 'd' || *format == 'i')
		ft_numbers_signed(va_arg(ap, int), data, 10, "0123456789");
	else if (*format == 'u')
		ft_numbers_unsigned(va_arg(ap, unsigned int), data, 10, "0123456789");
	else if (*format == 'x')
		ft_numbers_unsigned(va_arg(ap, unsigned int), data, 16,
			"0123456789abcdef");
	else if (*format == 'X')
		ft_numbers_unsigned(va_arg(ap, unsigned int), data, 16,
			"0123456789ABCDEF");
	else if (*format == 'p')
		ft_pointer(ap, data);
}

int	ft_printf(char const *format, ...)
{
	va_list	ap;
	int		data;

	va_start(ap, format);
	data = 0;
	while (*format)
	{
		if (*format == '%')
			ft_formats(++format, ap, &data);
		else
			ft_putchar(*format, &data);
		format++;
	}
	va_end(ap);
	return (data);
}
/*
int	main(void)
{
	ft_printf("%%%%%");
	ft_printf("\n");
	ft_printf("%c\n", 'h');
	ft_printf("hola %s\n", "como estas");
	ft_printf("num: %d\n", 134242);
	ft_printf("numu: %u\n", 134242);
	ft_printf("numi: %i\n", 134242);
	ft_printf("hex: %x\n", 424242);
	ft_printf("HEX: %X\n", 424242);
	ft_printf("point: %p %p\n", 0, 0);
	ft_printf("__________________________________\n");
	printf("%%\n");
	printf("%c\n", 'h');
	printf("hola %s\n", "como estas");
	printf("num: %d\n", 134242);
	printf("numu: %u\n", 134242);
	printf("numi: %i\n", 134242);
	printf("hex: %x\n", 424242);
	printf("HEX: %X\n", 424242);
	printf("point: %p\n", (void *)424242);
	return (0);
}*/
