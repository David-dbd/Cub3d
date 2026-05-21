/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:48:53 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:25:42 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

void	ft_numbers_signed(long n, int *data, unsigned long basesize,
		char *basestr)
{
	if (n < 0)
	{
		ft_putchar('-', data);
		n = -n;
	}
	if ((unsigned long)n >= basesize)
		ft_numbers_signed(n / basesize, data, basesize, basestr);
	if (*data == -1)
		return ;
	ft_putchar(basestr[n % basesize], data);
}

void	ft_numbers_unsigned(unsigned long n, int *data, unsigned long basesize,
		char *basestr)
{
	if (n >= basesize)
		ft_numbers_unsigned(n / basesize, data, basesize, basestr);
	if (*data == -1)
		return ;
	ft_putchar(basestr[n % basesize], data);
}
