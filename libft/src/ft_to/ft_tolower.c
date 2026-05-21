/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:54:24 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:16:37 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

/*int	main(void)
{
	printf("%c\n", ft_tolower('A'));
	printf("%c\n", ft_tolower('2'));
	printf("%c\n", ft_tolower(' '));
	printf("%c\n", ft_tolower('D'));
	return (0);
}*/
