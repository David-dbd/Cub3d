/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_search_system.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 01:29:51 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/04 00:31:48 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"
/*
int	apply_system_search(char **new_map)
{
	
}

int	directional_system(t_game *the_game)
{
	char	**new_map;
	int		n_lines;
	int		i;

	i = 0;
	n_lines = ft_count_str_in_arr(the_game->map.grid);
	new_map = malloc((n_lines + 1) * sizeof(char *));
	if (!new_map)
		return (print_error(NULL, LOCAL_ERROR));
	new_map[n_lines+ 1] = NULL;
	while (i < n_lines)
	{
		if (extract_map_line(new_map[i], the_game->map.grid[i], TRUE) == ERROR)
			return (ERROR);
		i++;
	} //at this point now we have our duplicate of the map and next is the algorithm
	if (apply_system_search(new_map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}*/

/*
	Here we find the global length of the matrix. Meaning, we start in 0 and
	we just have to find the longest line and reference it's last index
*/

static void	find_global_index(t_game *the_game)
{
	int	longest_str;

	the_game->map.global_start = 0;
	longest_str = ft_long_str_in_arr(the_game->map.grid); //returns the len of the longest str in an arr
	the_game->map.global_end = longest_str;
}

/*
	Here we find the real start of each line (where the first 1 is located at) and
	the real ending (where the last 1 is located at)
*/

static void	find_start_end(char *str, t_line_data *bounds)
{
	int	spaces_left;
	int	spaces_right;
	int	len;

	len = ft_strlen(str);
	spaces_left = ignore_spaces(str, 0, 0);
	spaces_right = ignore_spaces(str, len - 1, 1);
	bounds->line_start = spaces_left;
	bounds->line_end = spaces_right - spaces_left;
}

static int	find_each_line_index(t_game *the_game)
{
	int	i;

	i = 0;
	//the_game->map.lines = ft_calloc(the_game->map.height, sizeof(t_line_data));
	//if (!the_game->map.lines)
	//	return (print_error(NULL, 2));
	while (i < the_game->map.height)
	{
		find_start_end(the_game->map.grid[i], &the_game->map.lines[i]); //toma la linea en cuestion del mapa y verifica su inicio y final real
		the_game->map.lines[i].line_counter = i;
		i++;
	}
	return (SUCCESS);
}

void	start_search_system(t_game *the_game)
{
	find_global_index(the_game);
	if (find_each_line_index(the_game) == ERROR)
		exit_error(the_game);
	search_system_engine(the_game);
	printf("\n\nVALID MAP\n\n");
}