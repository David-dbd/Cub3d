/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:57:19 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/05/27 15:05:53 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"

static int	check_colors_range(int r, int g, int b)
{
	if (!(r >= 0 && r <= 255) || !(g >= 0 && g <= 255) || !(b >= 0 && b <= 255))
		return (0);
	return (1);
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
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (0);
		if (str[i] == ',')
			coma_counter++;
		i++;
	}
	if (coma_counter != 3)
		return (0);
	return (1);
}

static int	compare_colors(char *line, char **rgb_colors, char *letter)
{
	int		spaces_at_left;
	int		spaces_at_right;
	int		colors_len;

	spaces_at_left = 0;
	if (word_counter(line, 0) != 2)// 
		return (print_error(WRONG_C, LOCAL_ERROR));
	spaces_at_left = ignore_spaces(line, 0, 0);// ignore initial potential spaces
	if (ft_strncmp(line + spaces_at_left, letter, 3) != 0)
		return (print_error(WRONG_C, LOCAL_ERROR));
	spaces_at_left = ignore_spaces(line, spaces_at_left + 1, 0); //from "F "
	spaces_at_right = ignore_spaces(line, ft_strlen(line) - 1, 1);//igniore potential spaces
	*rgb_colors = ft_substr(line, spaces_at_left, ft_strlen(line) - spaces_at_right);
	if (!*rgb_colors)
		return (print_error(NULL, SYSTEM_CALL));
	colors_len = ft_strlen(*rgb_colors);
	if (colors_len < 5 || !only_numbers(*rgb_colors)) //RGB 0,0,0 or hello,120,130 or 111111 or -1,-12...
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
	r = ft_atoi(colors_arr[0]);
	g = ft_atoi(colors_arr[1]);
	b = ft_atoi(colors_arr[2]);
	if (!check_colors_range(r, g, b))
		return (free (rgb_colors), ft_free_str_array(&colors_arr),
			print_error(WRONG_C, LOCAL_ERROR));
	if (letter[0] == 'F')
		the_game->config.floor_color = (r << 16) | (g << 8) | b;
	else
		the_game->config.ceiling_color = (r << 16) | (g << 8) | b;
	ft_free_str_array(&colors_arr);
	free (rgb_colors);
	return (SUCCESS);
}

int	parse_colors(t_game *the_game, int cub_fd)
{
	char	*letter[2] = {"F", "C"};
	char	*line;
	char	*rgb_colors;
	int		index;
	int		error_track;

	index = 0;
	while ((line = get_next_line(cub_fd)) != NULL && index < 2)
	{
		error_track = compare_colors(line, &rgb_colors, letter[index]);
		if (error_track != SUCCESS)
			return (error_track);
		error_track = copy_colors(the_game, rgb_colors, letter[index]);
		if (error_track != SUCCESS)
			return (free (line),free (rgb_colors), error_track);
		free (line);
		free (rgb_colors);
		line = NULL;
		index++;
	}
	if (!line && !index)
		return (print_error(EMPTY_FILE, LOCAL_ERROR));
	if (index != 2)
		return (free (line), free (rgb_colors), print_error(WRONG_C, LOCAL_ERROR));
	return (SUCCESS);
}
