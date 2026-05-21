/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:39:06 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/05/22 00:34:49 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/cub3d.h"

/*
	Detects a wall is always 1's and counts it. There should always be 2 full_l
*/

static int	is_full_line(char *line, int *full_lines)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1')
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

static int	is_middle_line(char *line, int *full_lines, int line_type, int *player_count)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (line_type == FULL_LINE || (line_type == FALSE && *full_lines == 0))
		return (FALSE);
	while (line[i] != '\0')
	{
		if ((i == 0 && line[i] != '1') || (i == len - 1 && line[i] != '1'))
			return (FALSE);
		if ((i > 0 && i < len - 1) && (line[i] != '0' && line[i] != '1'))
		{
			if (line[i] != 'N' && line[i] != 'E' && line[i] != 'S' && line[i] != 'W')
				return (FALSE);
			else
			{
				if (*player_count == 1)
					return (FALSE);
				(*player_count)++;
			}
		}
		i++;
	}
	return (TRUE);
}

/*
	Detects whether a line is full (111) or middle line. It uses line_type as
	a flag to know what line of the is. If it is a full line, then is_middle_line
	will detect it and wont change its state. The full_lines counter is another
	layer of valdiation. It should be 2 at the end of the process (first and last line).
	If the line_ryoe ends up being FALSE it means the line of the map we just
	read is wrong
*/

static int	examine_line(char **map_line, int *full_lines, int *player_count)
{
	int	line_type;

	line_type = FALSE;
	if (is_full_line(*map_line, full_lines))
		line_type = FULL_LINE;
	else if (is_middle_line(*map_line, full_lines, line_type, player_count))
		line_type = MIDDLE_LINE;
	if (line_type == FALSE)
		return (print_error(WRONG_M, LOCAL_ERROR));
	return (SUCCESS);
}

static int	extract_map_line(char **map_line, char *line)
{
	int	spaces_at_left;
	int	spaces_at_right;
	int	line_len;

	spaces_at_left = 0;
	if (word_counter(line, 0) != 1)// "111 111 111"
		return (print_error(WRONG_P, LOCAL_ERROR));
	spaces_at_left = ignore_spaces(line, 0, "right");
	spaces_at_right = ignore_spaces(line, ft_strlen(line) - 1, "left");
	*map_line = ft_substr(line, spaces_at_left, ft_strlen(line) - spaces_at_right);
	if (!*map_line)
		return (print_error(NULL, SYSTEM_CALL));
	line_len = ft_strlen(*map_line);
	if (line_len < 3) //at least 111
		return (print_error(WRONG_P, LOCAL_ERROR));
	return (SUCCESS);
}

int	parse_map(t_game *the_game, int fd)
{
	char	*line;
	int		full_lines;
	int		index;
	int		player_counter;

	index = 0;
	full_lines = 0;
	player_counter = 0;
	line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (add_slot_to_arr(the_game->map.grid, index) == ERROR)
			return (free(line), ERROR);
		if (extract_map_line(&the_game->map.grid[index], line) == ERROR)
			return (free(line), ERROR);
		if (examine_line(&the_game->map.grid[index], &full_lines, &player_counter) == ERROR)
			return (free(line), ERROR);
		free (line);
		index++;
	}
	if (full_lines != 2 || player_counter != 1)
		return (free (line), print_error(WRONG_M, LOCAL_ERROR));
	if (calculate_width_height(the_game->map) == ERROR)
		return (free (line), print_error(WRONG_M, LOCAL_ERROR));
	return (SUCCESS);
}
