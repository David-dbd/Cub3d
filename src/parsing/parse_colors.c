/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:57:19 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/06/19 02:44:43 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"

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
	*b = ft_atoi(trimmed); //liberar
	free (trimmed);
	
	return (SUCCESS);
}

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
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != ' ')
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
	int		spaces_at_left;
	int		spaces_at_right;
	int		colors_len;

	spaces_at_left = 0;
	if (word_counter(line, 0) != 4)// 
		return (print_error(WRONG_C, LOCAL_ERROR));
	spaces_at_left = ignore_spaces(line, 0, 0);// ignore initial potential spaces
	if (ft_strncmp(line + spaces_at_left, letter, 1) != 0)
		return (print_error(WRONG_C, LOCAL_ERROR));
	spaces_at_left = ignore_spaces(line, spaces_at_left + 1, 0); //from "F "
	spaces_at_right = ignore_spaces(line, ft_strlen(line) - 1, 1);//igniore potential spaces
	*rgb_colors = ft_substr(line, spaces_at_left, spaces_at_right - spaces_at_left + 1);
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
	if (delete_spaces(&r, &b, &g, colors_arr) == ERROR)
	{
		printf("aquiiiiiii");
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
	rgb_colors = NULL;
	while ((line = get_next_line(cub_fd)) != NULL && index < 2)
	{
		error_track = compare_colors(line, &rgb_colors, letter[index]);
		if (error_track != SUCCESS)
			return (error_track);
		error_track = copy_colors(the_game, rgb_colors, letter[index]);
		if (error_track != SUCCESS)
			return (free (line), error_track);
		free (line);
		line = NULL;
		index++;
	}
	if (!line && !index)
		return (print_error(EMPTY_FILE, LOCAL_ERROR));
	if (index != 2)
		return (free (line), print_error(WRONG_C, LOCAL_ERROR));
	return (SUCCESS);
}
