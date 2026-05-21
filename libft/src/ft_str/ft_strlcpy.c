/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:22:38 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:15:08 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (ft_strlen((char *)src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (ft_strlen((char *)src));
}
/*
int	main(void)
{
	char *src = "Feliz 2025!";
	char dst[50];

	printf("%s > src.\n", src);
	printf("%zu bytes copied to dst (capacity: 5).\n", ft_strlcpy(dst, src, 5));
	printf("Truncated dst: %s\n", dst);

	return (0);
}*/
