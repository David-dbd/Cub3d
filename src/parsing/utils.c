/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 20:11:57 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/04/21 16:32:35 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/cub3d.h"

int	ignore_espaces(char *line, int k, int direction)
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
		start = ignore_spaces(line, start, "right");
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
	// copiar lo anterior
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

int	calculate_width_height(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	map->height = 0;
	map->width = 0;
	while (map->grid[i])
	{
		len = ft_strlen(map->grid[i]);
		if (len > map->width)
			map->width = len;
		i++;
	}
	map->height = i;
}
