/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:57:19 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/16 14:35:05 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	delete_spaces(int *r, int *b, int *g, char **colors_arr)
{
	char	*trimmed;

	trimmed = ft_strtrim(colors_arr[0], " ");
	if (!trimmed)
		return (ERROR);
	*r = ft_atoi(trimmed);
	free (trimmed);
	trimmed = ft_strtrim(colors_arr[1], " ");
	*g = ft_atoi(trimmed);
	free (trimmed);
	trimmed = ft_strtrim(colors_arr[2], " ");
	*b = ft_atoi(trimmed);
	free (trimmed);
	return (SUCCESS);
}

/*
	This will check for both letters and negative numbers. saving us time
	by not using atoi so early
*/

static	int	only_numbers(const char *str)
{
	int	i;
	int	coma_counter;

	i = 0;
	coma_counter = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != ' '
			&& str[i] != '\t')
			return (0);
		if (str[i] == ',')
			coma_counter++;
		i++;
	}
	if (coma_counter != 2)
		return (0);
	return (1);
}

static int	compare_colors(char *line, char **rgb_colors, char *letter)
{
	int	spaces_left;
	int	spaces_right;
	int	colors_len;

	spaces_left = 0;
	if (word_counter(line, 0) != 4)
		return (print_error(WRONG_C, LOCAL_ERROR));
	spaces_left = ignore_spaces(line, 0, 0);
	if (ft_strncmp(line + spaces_left, letter, 1) != 0)
		return (print_error(WRONG_C, LOCAL_ERROR));
	spaces_left = ignore_spaces(line, spaces_left + 1, 0);
	spaces_right = ignore_spaces(line, ft_strlen(line) - 1, 1);
	*rgb_colors = ft_substr(line, spaces_left, spaces_right - spaces_left + 1);
	if (!*rgb_colors)
		return (print_error(NULL, SYSTEM_CALL));
	colors_len = ft_strlen(*rgb_colors);
	if (colors_len < 5 || !only_numbers(*rgb_colors))
		return (free(*rgb_colors), print_error(WRONG_C, LOCAL_ERROR));
	return (SUCCESS);
}

static int	copy_colors(t_game *the_game, char *rgb_colors, char *letter)
{
	char	**colors_arr;
	int		r;
	int		g;
	int		b;

	colors_arr = ft_split(rgb_colors, ',');
	if (!colors_arr)
		return (free (rgb_colors), print_error(WRONG_C, LOCAL_ERROR));
	if (ft_count_str_in_arr(colors_arr) != 3)
		return (free (rgb_colors), ft_free_str_array(&colors_arr),
			print_error(WRONG_C, LOCAL_ERROR));
	if (delete_spaces(&r, &b, &g, colors_arr) == ERROR)
	{
		return (free (rgb_colors), ft_free_str_array(&colors_arr),
			print_error(WRONG_C, LOCAL_ERROR));
	}
	if (!check_colors_range(r, g, b))
		return (free (rgb_colors), ft_free_str_array(&colors_arr),
			print_error(WRONG_C, LOCAL_ERROR));
	if (letter[0] == 'F')
		the_game->config.floor_color = (r << 16) | (g << 8) | b;
	else
		the_game->config.ceiling_color = (r << 16) | (g << 8) | b;
	ft_free_str_array(&colors_arr);
	return (free (rgb_colors), SUCCESS);
}

int	parse_colors(t_game *the_game, char *line, int index)
{
	char	*letter[2];
	char	*rgb_colors;
	int		error_track;

	letter[0] = "F";
	letter[1] = "C";
	rgb_colors = NULL;
	error_track = compare_colors(line, &rgb_colors, letter[index]);
	if (error_track != SUCCESS)
		return (error_track);
	error_track = copy_colors(the_game, rgb_colors, letter[index]);
	if (error_track != SUCCESS)
		return (error_track);
	return (SUCCESS);
}
