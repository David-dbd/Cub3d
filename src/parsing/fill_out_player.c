/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_out_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 00:36:54 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/15 11:14:55 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	remember the y axis is inverted
*/

static void	find_direction(char letter, double *dir_x, double *dir_y)
{
	if (letter == 'N')
	{
		*dir_x = 0;
		*dir_y = -1;
	}
	else if (letter == 'S')
	{
		*dir_x = 0;
		*dir_y = 1;
	}
	else if (letter == 'W')
	{
		*dir_x = -1;
		*dir_y = 0;
	}
	else if (letter == 'E')
	{
		*dir_x = 1;
		*dir_y = 0;
	}
}

static void	find_player(t_game *the_game, char **map, double *x, double *y)
{
	int	line;
	int	column;

	line = 0;
	while (map[line])
	{
		column = 0;
		while (map[line][column] != '\0')
		{
			if (ft_isalpha(map[line][column]))
			{
				*x = column + 0.5;
				*y = line + 0.5;
				the_game->player.start_dir = map[line][column];
				find_direction(map[line][column],
					&the_game->player.dir_x, &the_game->player.dir_y);
				return ;
			}
			column++;
		}
		line++;
	}
}

static void	find_plane( double *pl_x, double *pl_y, double dir_x, double dir_y)
{
	double	fov;

	fov = 0.66;
	*pl_x = dir_y * fov;
	*pl_y = -dir_x * fov;
}

void	fill_out_player(t_game *the_game)
{
	find_player(the_game, the_game->map.grid, &the_game->player.x, 
		&the_game->player.y);
	find_plane(&the_game->player.plane_x, &the_game->player.plane_y,
		the_game->player.dir_x, the_game->player.dir_y);
}