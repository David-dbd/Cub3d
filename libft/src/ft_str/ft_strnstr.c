/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:51:15 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:15:48 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	i = ft_strlen(little);
	if (i > len)
		return (NULL);
	while (*big && len >= i)
	{
		if (ft_strncmp((char *)big, (char *)little, i) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

/*int main(void)
{
	char *result;

	result = ft_strnstr("hello world", "world", 11);
	if (result != NULL)
		printf("Found: %s\n", result); // Expected: "world"
	else
		printf("Not found\n");

	return (0);
}*/
