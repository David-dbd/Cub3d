/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 11:21:35 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/13 11:37:19 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	*build_row_lengths(char **grid, int height)
{
	int	*lengths;
	int	i;

	lengths = malloc(sizeof(int) * height);
	if (!lengths)
		return (NULL);
	i = 0;
	while (i < height)
	{
		lengths[i] = ft_strlen(grid[i]);
		i++;
	}
	return (lengths);
}

int	build_scene(t_game *the_game, t_cub3d_scene *scene)
{
	scene->map = the_game->map.grid;
	scene->map_width = the_game->map.width;
	scene->map_height = the_game->map.height;
	scene->row_lengths = build_row_lengths(the_game->map.grid,
			the_game->map.height);
	if (!scene->row_lengths)
		return (print_error(NULL, SYSTEM_CALL));
	scene->textures[CUB3D_TEX_NO] = the_game->config.path[0];
	scene->textures[CUB3D_TEX_SO] = the_game->config.path[1];
	scene->textures[CUB3D_TEX_WE] = the_game->config.path[2];
	scene->textures[CUB3D_TEX_EA] = the_game->config.path[3];
	scene->floor_color = the_game->config.floor_color;
	scene->ceiling_color = the_game->config.ceiling_color;
	scene->player_x = the_game->player.x;
	scene->player_y = the_game->player.y;
	scene->player_dir = the_game->player.start_dir;
	scene->screen_width = 0;   // 0 -> el motor aplica CUB3D_DEFAULT_WIDTH/HEIGHT
	scene->screen_height = 0;
	return (SUCCESS);
}