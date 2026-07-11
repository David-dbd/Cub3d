/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_sections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 01:05:59 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/11 19:01:59 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"

static int	recognize_line(char *line, int *orientation_flag, int *colors_flag)
{
	int	idx;

	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (IGNORE);
	idx = get_path_index(line);
	if (idx != -1)
	{
		if (orientation_flag[idx] == FALSE)
			return (ERROR); // duplicado
		orientation_flag[idx] = FALSE;
		return (PATH_LINE);
	}
	idx = get_color_index(line);
	if (idx != -1)
	{
		if (colors_flag[idx] == FALSE)
			return (ERROR); // duplicado
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


int	figure_sections(t_game *the_game, int cub_fd)
{
	char	*line;
	int		result;
	int		index;
	int		orien_flag[4] = {1, 1, 1, 1};
	int		colors_flag[2] = {1, 1};

	index = 0;
	line = NULL;
	while (check_flags(orien_flag, colors_flag) 
		&& (line = get_next_line(cub_fd)) != NULL)
	{
		result = recognize_line(line, orien_flag, colors_flag);
		if (result == PATH_LINE || result == COLOR_LINE)
		{
			if (parse_line(the_game, line, result) == ERROR)
				return (free(line), ERROR);
		}
		else if (result != PATH_LINE && result != COLOR_LINE 
				&& result != IGNORE)
			return (print_error(INVALID_C, LOCAL_ERROR), free (line), ERROR);
		free(line);
		index++;
	}
	if (!line && !index) //añadir una funcion que revise si ambos arr_flags estan en 0 completamente, meaning we had all matches
		return (print_error(EMPTY_FILE, LOCAL_ERROR));
	return (SUCCESS);
}
