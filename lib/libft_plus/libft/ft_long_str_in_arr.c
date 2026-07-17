/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_str_in_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:52:40 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/17 12:43:10 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_plus.h"

int	ft_long_str_in_arr(char **arr)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!arr)
		return (0);
	len = ft_strlen(arr[i]);
	while (arr[i])
	{
		if (len < (int)ft_strlen(arr[i]))
			len = ft_strlen(arr[i]);
		i++;
	}
	return (len);
}
