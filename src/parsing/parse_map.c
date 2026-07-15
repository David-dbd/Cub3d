/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:39:06 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/15 10:45:57 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	Detects a wall is always 1's and counts it. There should always be 2 full_l
*/

static int	is_full_line(char *line, int distance, int *full_lines)
{
	int	i;

	i = 0;
	while (i < distance)
	{
		if (line[i] != '1' && line[i] != ' ')
			return (FALSE);
		i++;
	}
	*full_lines += 1;
	return (TRUE);
}

/*
	Detects a middle_line. Checks that always has 1's or 0's. If not, it checks
	for player postion. It detects when there's more than 1 letter per line.
	Also checks that starts in 1 and closes in 1. 
	If a line is already full then we return
*/

static int	is_mid_line(char *line, int *line_type, int distan, t_rules *rules)
{
	int	i;

	i = 0;
	if (*line_type == TOP_LINE || *line_type == BOTTOM_LINE 
		|| (*line_type == FALSE && rules->full_lines == 0))
		return (FALSE);
	while ((i++) < distan)
	{
		if ((i == 0 && line[i] != '1') || (i == distan - 1 && line[i] != '1'))
			return (FALSE);
		if ((i > 0 && i < distan - 1) 
			&& (line[i] != '0' && line[i] != '1' && line[i] != ' '))
		{
			if (line[i] != 'N' && line[i] != 'E' && line[i] != 'S' 
					&& line[i] != 'W')
				return (FALSE);
			else
			{
				if (rules->player_counter == 1)
					return (FALSE);
				(rules->player_counter)++;
			}
		}
	}
	return (TRUE);
}

/*
	Detects whether a line is full (111) or middle line. It uses line_type as
	a flag to know what line of the is. If it is a full line, then 
	is_middle_line will detect it and wont change its state. The full_lines 
	counter is another layer of valdiation. It should be 2 at the end of the 
	process (first and last line).
	If the line_ryoe ends up being FALSE it means the line of the map we just
	read is wrong
*/

static int	check_line(char *map_line, int *line_type, t_rules *rules)
{
	int len;
	int	spaces_at_left;
	int	spaces_at_right;
	int distance = 0;

	*line_type = FALSE;
	len = ft_strlen(map_line);
	if (len == 0)
		return (print_error(WRONG_M, LOCAL_ERROR));
	spaces_at_left = ignore_spaces(map_line, 0, 0);
	spaces_at_right = ignore_spaces(map_line, len - 1, 1);
	distance = spaces_at_right - spaces_at_left + 1;
	if (is_full_line(map_line + spaces_at_left, distance, &rules->full_lines))
	{
		if (rules->full_lines == 1)
			*line_type = TOP_LINE;
		else if (rules->full_lines >= 2)
			*line_type = BOTTOM_LINE;
	}
	else if (is_mid_line(map_line + spaces_at_left, line_type, distance, rules))
		*line_type = MIDDLE_LINE;
	if (*line_type == FALSE)
		return (print_error(WRONG_M, LOCAL_ERROR));
	return (SUCCESS);
}

int	parse_map(t_game *the_game, int fd)
{
	t_rules	rules;
	char	*line;
	int		index;

	index = 0;
	rules = (t_rules){0};
	line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (add_slot(&the_game->map.grid, &the_game->map.lines, index) == ERROR)
			return (free(line), ERROR);
		if (check_line(line, &the_game->map.lines[index].line_type, 
			&rules) == ERROR)
			return (free(line), ERROR);
		if (extract_map_line(&the_game->map.grid[index], line) == ERROR)
			return (free(line), ERROR);
		free (line);
		index++;
	}
	if (calculate_width_height(&the_game->map) == ERROR)
		return (free (line), print_error(WRONG_M, LOCAL_ERROR));
	return (SUCCESS);
}