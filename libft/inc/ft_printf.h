/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:09:22 by pestell2          #+#    #+#             */
/*   Updated: 2025/02/10 13:23:06 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		ft_printf(char const *format, ...);
void	ft_pointer(va_list ap, int *data);
void	ft_numbers_signed(long n, int *data, unsigned long basesize,
			char *basestr);
void	ft_putstr(char *str, int *data);
void	ft_putchar(int c, int *data);
void	ft_numbers_unsigned(unsigned long n, int *data, unsigned long basesize,
			char *basestr);
#endif
