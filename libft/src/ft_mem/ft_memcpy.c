/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:41:23 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:12:31 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < size)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	const char	src[50] = "Tutorialspoint";
	char		dest[50];

	ft_strlcpy(dest, "Heloooo!!", 20);
	printf("Before memcpy dest = %s\n", dest);
	ft_memcpy(dest + 2, src, 7);
	printf("After memcpy dest = %s\n", dest);
	return (0);
}*/
