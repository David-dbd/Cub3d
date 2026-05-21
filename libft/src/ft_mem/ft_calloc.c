/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:42:38 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:12:09 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb != 0 && size != 0 && size > ((size_t)-1) / nmemb)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return ((void *)mem);
}

/*
#include <stdio.h>

int	main(void)
{
	int	*ptr;
	int	*ptr2;

	ptr = ft_calloc(-5, 0);
	ptr2 = malloc(-5 * 0);
	printf("%p\n", ptr);
	printf("%p\n", ptr2);
	free(ptr);
	free(ptr2);
	return (0);
}
*/
