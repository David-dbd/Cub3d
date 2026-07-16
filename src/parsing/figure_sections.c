/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_sections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 01:05:59 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/16 14:17:07 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	helper(int *orien_flag, int *colors_flag, int *index)
{
	orien_flag[0] = 1;
	orien_flag[1] = 1;
	orien_flag[2] = 1;
	orien_flag[3] = 1;
	colors_flag[0] = 1;
	colors_flag[1] = 1;
	*index = 0;
}

static int	recognize_line(char *line, int *orientation_flag, int *colors_flag)
{
	int	idx;

	if (is_empty_line(line))
		return (IGNORE);
	idx = get_path_index(line);
	if (idx != -1)
	{
		if (orientation_flag[idx] == FALSE)
			return (ERROR);
		orientation_flag[idx] = FALSE;
		return (PATH_LINE);
	}
	idx = get_color_index(line);
	if (idx != -1)
	{
		if (colors_flag[idx] == FALSE)
			return (ERROR);
		colors_flag[idx] = FALSE;
		return (COLOR_LINE);
	}
	return (ERROR);
}

static int	parse_line(t_game *the_game, char *line, int result)
{
	int	element_index;

	if (result == PATH_LINE)
	{
		element_index = get_path_index(line);
		if (element_index == -1)
			return (ERROR);
		if (parse_paths(the_game, line, element_index) != SUCCESS)
			return (ERROR);
		return (SUCCESS);
	}
	if (result == COLOR_LINE)
	{
		element_index = get_color_index(line);
		if (element_index == -1)
			return (ERROR);
		if (parse_colors(the_game, line, element_index) != SUCCESS)
			return (ERROR);
		return (SUCCESS);
	}
	return (ERROR);
}

static int	check_flags(int *orientation_flag, int *colors_flag)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (orientation_flag[i] != 0)
			return (TRUE);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (colors_flag[i] != 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	figure_sections(t_game *the_game, int cub_fd, char	**line, char **pending)
{
	int		resul;
	int		index;
	int		orien_flag[4];
	int		colors_flag[2];

	helper(orien_flag, colors_flag, &index);
	*line = get_next_line(cub_fd);
	while (check_flags(orien_flag, colors_flag) && (*line != NULL))
	{
		resul = recognize_line(*line, orien_flag, colors_flag);
		if (resul == PATH_LINE || resul == COLOR_LINE)
		{
			if (parse_line(the_game, *line, resul) == ERROR)
				return (free(*line), ERROR);
		}
		else if (resul != PATH_LINE && resul != COLOR_LINE && resul != IGNORE)
			return (print_error(INVALID_C, LOCAL_ERROR), free (*line), ERROR);
		free(*line);
		index++;
		*line = get_next_line(cub_fd);
	}
	if (!*line && !index)
		return (print_error(EMPTY_FILE, LOCAL_ERROR));
	*pending = *line;
	return (SUCCESS);
}
