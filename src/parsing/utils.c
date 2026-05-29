/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 20:11:57 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/05/28 10:05:23 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"

int	ignore_spaces(char *line, int k, int direction)
{
	if (direction == 1)
	{
		while (k > 0 && (line[k] == ' ' || line[k] == '\t'))
			k--;
		return (k);
	}
	while (line[k] != '\0' && (line[k] == ' ' || line[k] == '\t'))
		k++;
	return (k);
}

int	word_counter(char *line, int start)
{
	int	count;

	count = 0;
	while (line[start] != '\0')
	{
		start = ignore_spaces(line, start, 0);
		count++;
		while (line[start] != '\0' && line[start] != ' ' && line[start] != '\t')
			start++;
	}
	return (count);
}

int	add_slot_arr(char ***map, int index)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (index + 2));
	if (!new)
		return (ERROR);
	while (i < index)
	{
		new[i] = (*map)[i];
		i++;
	}
	new[index] = NULL;
	new[index + 1] = NULL;
	free (*map);
	*map = new;
	return (SUCCESS);
}

int calculate_width_height(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	if (!map || !map->grid)
		return (ERROR);
	map->width = 0;
	while (map->grid[i])
	{
		len = ft_strlen(map->grid[i]);
		if (len == 0)// la línea vacía
			return (ERROR);
		if (len > map->width)
			map->width = len;
		i++;
	}
	if (i == 0)//o el mapa esta vacio error
		return (ERROR);
	map->height = i;
	return (SUCCESS);
}
