/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:45:20 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:15:57 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	s[11] = "Hola amigos";
	char		c;
	char 		*ret;

	c = 'g';
	printf("s=%s\t", s);
	printf("c=%c\n", c);
	ret = ft_strrchr(s, c);
	printf("String after |%c| is - |%s|\n", c, ret);
	return (0);
}*/
