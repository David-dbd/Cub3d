/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:07:05 by pestell2          #+#    #+#             */
/*   Updated: 2025/05/02 12:13:52 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!(result))
		return (NULL);
	ft_strlcpy(result, s, ft_strlen(s) + 1);
	result[ft_strlen(s)] = '\0';
	return (result);
}

/*int	main()
{
	const char *s = "hola";

	printf("%s", ft_strdup(s));
	return 0;
}*/
