/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:10:00 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:13:59 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while ((int)i != ft_strlen(s))
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}
/*
void	print_index_and_char(unsigned int index, char *c)
{
	printf("Index: %u, Character: %c\n", index, *c);
}

int	main(void)
{
	char	str[] = "Hello, World!";

	ft_striteri(str, print_index_and_char);
	return (0);
}*/
