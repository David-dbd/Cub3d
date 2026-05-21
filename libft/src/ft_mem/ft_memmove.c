/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:30:27 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:12:38 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d > s)
		while (n--)
			d[n] = s[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
/*
int	main(void)
{
	char src[] = "holacomoesras";

	ft_memmove(src + 2, src, strlen(src) + 1);
	printf("%s\n", src);

	char src2[] = "holacomoesras";
	memmove(src2 + 2, src2, strlen(src2) + 1);
	printf("%s\n", src2);
	return (0);
}*/
