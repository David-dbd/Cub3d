/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_out_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 00:36:54 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/05/22 01:09:36 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/cub3d.h"

void	find_direction(char letter, double *dir_x, double *dir_y)//remember the y axis is inverted
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

void	find_player(t_game *the_game, char **map, double *x, double *y)
{
	int	line;
	int	column;

	line = 0;
	column = 0;
	while (map[line])
	{
		while (map[column][line] != '\0')
		{
			if (ft_isalpha(map[line][column]))
			{
				*x = column + 0.5;
				*y = line + 0.5;
				find_direction(map[line][column], &the_game->player.dir_x, &the_game->player.dir_y);
				return ;
			}
			column++;
		}
		line++;
	}
}

void	find_plane( double *plane_x, double *plane_y, double dir_x, double dir_y)
{
	double	fov;

	fov = 0.66;
	*plane_x = dir_y * fov;
	*plane_y = -dir_x * fov;
}

void	fill_out_player(t_game *the_game)
{
	find_player(the_game, the_game->map.grid, &the_game->player.x, &the_game->player.y);
	find_plane(&the_game->player.plane_x, &the_game->player.plane_y, the_game->player.dir_x, the_game->player.dir_y);
}