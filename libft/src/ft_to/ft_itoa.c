/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:22:40 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:16:29 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_operation(char *res, unsigned int num, long int len)
{
	while (num > 0)
	{
		res[len--] = 48 + (num % 10);
		num = num / 10;
	}
	return (res);
}

int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	num;
	long int		len;

	len = count_digits(n);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (n == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (n < 0)
	{
		num = -n;
		res[0] = '-';
	}
	else
		num = n;
	ft_operation(res, num, len);
	return (res);
}
/*
int	main(void)
{
	int		number;
	char	*res;

	number = -123653;
	res = ft_itoa(number);
	printf("The number %s.\n", res);
	free(res);
	return (0);
}*/
