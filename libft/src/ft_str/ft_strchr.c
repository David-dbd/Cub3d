/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:45:20 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:13:46 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s != '\0' && uc != *s)
		s++;
	if (uc == *s)
		return ((char *)s);
	return (0);
}

/*
int	main(void)
{
	const char	s[11] = "Hola amigos";
	char		c;

	c = 'a';
	printf("s=%s\t", s);
	printf("c=%c\n", c);
	printf("strchr=%s\n", ft_strchr(s, c));
	return (0);
}*/
