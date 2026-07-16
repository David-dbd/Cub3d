/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_search_system.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 01:29:51 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/16 12:59:25 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	Here we find the real start of each line (where the first 1 is located at) 
	and the real ending (where the last 1 is located at)
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
	while (i < the_game->map.height)
	{
		find_start_end(the_game->map.grid[i], &the_game->map.lines[i]);
		the_game->map.lines[i].line_counter = i;
		i++;
	}
	return (SUCCESS);
}

void	start_search_system(t_game *the_game)
{
	if (find_each_line_index(the_game) == ERROR)
		exit_error(the_game);
	search_system_engine(the_game);
}
