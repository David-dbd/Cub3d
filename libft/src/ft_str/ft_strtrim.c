/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:52:30 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:16:04 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*x;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
	{
		s1++;
	}
	if (*s1 == '\0')
		return (ft_strdup(""));
	len = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[len]))
	{
		len--;
	}
	x = ft_substr(s1, 0, len + 1);
	return (x);
}
