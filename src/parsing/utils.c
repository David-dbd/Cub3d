/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 20:11:57 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/13 11:37:12 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int ignore_spaces(char *line, int index, int direction)
{
	if (direction == 0) // left to right -> ->
	{
		while (line[index] == ' ' || line[index] == '\t'
			|| line[index] == '\n' || line[index] == '\r')
			index++;
		return (index);
	}
	else // right to left <- <-
	{
		while (index >= 0 && (line[index] == ' ' || line[index] == '\t'
			|| line[index] == '\n' || line[index] == '\r'))
			index--;
		return (index);
	}
}


int word_counter(char *line, int start)
{
	int count;

	count = 0;
	while (line[start] != '\0')
	{
		start = ignore_spaces(line, start, 0);  //usar índice absoluto
		if (line[start] == '\0')
			break;
		count++;
		while (line[start] != '\0' && line[start] != ' ' && line[start] != '\t')
			start++;
	}
	return (count);
}

t_line_data *add_line_slot(t_line_data *arr, int count)
{
	t_line_data	*new;

	new = realloc(arr, sizeof(t_line_data) * (count + 1));
	if (!new)
		return (NULL);
	new[count] = (t_line_data){0};
	return (new);
}

int	add_slot(char ***map, t_line_data **line, int index)
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
	*line = add_line_slot(*line, index);
	if (!*line)
		return (print_error(NULL, SYSTEM_CALL), ERROR);
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
