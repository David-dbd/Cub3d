/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:03:48 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:25:49 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

void	ft_pointer(va_list ap, int *data)
{
	void	*ptr;

	ptr = va_arg(ap, void *);
	if (ptr == NULL)
		ft_putstr("(nil)", data);
	else
	{
		ft_putstr("0x", data);
		ft_numbers_unsigned((unsigned long)ptr, data, 16, "0123456789abcdef");
	}
}
