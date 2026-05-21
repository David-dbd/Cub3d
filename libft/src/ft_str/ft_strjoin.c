/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:13:42 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:14:05 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	res = malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	ft_strlcpy(res, s1, s1_len + 1);
	ft_strlcat(res, s2, (s1_len + s2_len + 1));
	return (res);
}
/*
int	main(void)
{
	const char	src[6] = "montes";
	char		dest[7] = "felipe ";
	char		*result;

	// Test ft_strlcat
	result = ft_strjoin(dest, src);
	printf("Custom ft_strlcat: %s\n", result);
	return (0);
}*/
