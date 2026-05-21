/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_str_in_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 21:45:57 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/04/17 21:46:05 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_count_str_in_arr(char **arr)
{
	int	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count] != NULL)
		count++;
	return (count);
}