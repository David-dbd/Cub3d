/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:39:42 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/13 11:39:42 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	search_left(t_map *map, int line_index, int space_index, int context)
{
	char	*str;
	int		i;

	i = space_index;
	str = map->grid[line_index];
	if (context == OUTSIDE_SPACE_LEFT)
		return (IGNORE);
	while (i > map->lines[line_index].line_start)
	{
		if (str[i] == '0' || ft_isalpha(str[i]))
			return (ERROR);
		if (str[i] == '1')
			return (SUCCESS);
		i--;
	}
	return (ERROR); //if it was an inside space or outside right space it should've found a 1
}

int	search_right(t_map *map, int line_index, int space_index, int context)
{
	char	*str;
	int		i;
	int		len;

	i = space_index;
	len = map->lines[line_index].line_end;
	str = map->grid[line_index];
	if (context == OUTSIDE_SPACE_RIGHT)
		return (IGNORE);
	while (i < len)
	{
		if (str[i] == '0' || ft_isalpha(str[i]))
			return (ERROR);
		if (str[i] == '1')
			return (SUCCESS);
		i++;
	}
	return (ERROR); //if it was an inside space or outside right space it should've found a 1
}

int	search_top(t_map *map, int space_index, t_line_data *lines, int context)
{
	int	i;
	int	str_pos;

	i = space_index;
	str_pos = lines->line_counter;
	if (lines->line_type == TOP_LINE 
		|| context == OUTSIDE_SPACE_RIGHT || context == OUTSIDE_SPACE_LEFT)
		return (IGNORE);
	while (str_pos >= 0)
	{
		if (map->grid[str_pos][i] == '0' || ft_isalpha(map->grid[str_pos][i]))
			return (ERROR);
		if (map->grid[str_pos][i] == '1')
			return (SUCCESS);
		str_pos--;
	}
	return (ERROR); //if it was an inside space or outside right space it should've found a 1
}

int	search_bottom(t_map *map, int space_index, t_line_data *lines, int context)
{
	int	i;
	int	str_pos;

	i = space_index;
	str_pos = lines->line_counter; //beacuse I need to know what index the str is in the matrix
	if (lines->line_type == BOTTOM_LINE 
			|| context == OUTSIDE_SPACE_RIGHT || context == OUTSIDE_SPACE_LEFT)
		return (IGNORE);
	while (map->grid[str_pos] != NULL)
	{
		if (map->grid[str_pos][i] == '0' || ft_isalpha(map->grid[str_pos][i]))
			return (ERROR);
		if (map->grid[str_pos][i] == '1')
			return (SUCCESS);
		str_pos++;
	}
	return (ERROR); //if it was an inside space or outside right space it should've found a 1
}