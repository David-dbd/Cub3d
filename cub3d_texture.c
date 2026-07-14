/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:35:18 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static char	cub3d_scene_cell(t_cub3d_scene *scene, int x, int y)
{
	char	cell;

	if (x < 0 || y < 0 || y >= scene->map_height)
		return ('1');
	if (scene->row_lengths && x >= scene->row_lengths[y])
		return ('1');
	if (!scene->row_lengths && x >= scene->map_width)
		return ('1');
	cell = scene->map[y][x];
	if (cell == '\0' || cell == ' ')
		return ('1');
	return (cell);
}

static int	cub3d_validate_player(t_cub3d_scene *scene)
{
	char	cell;

	if (scene->player_dir != 'N' && scene->player_dir != 'S'
		&& scene->player_dir != 'W' && scene->player_dir != 'E')
	{
		cub3d_error("invalid player direction");
		return (0);
	}
	if (scene->player_x < 0.0 || scene->player_y < 0.0)
	{
		cub3d_error("invalid player position");
		return (0);
	}
	cell = cub3d_scene_cell(scene, (int)scene->player_x,
			(int)scene->player_y);
	if (cell == '1')
	{
		cub3d_error("player starts inside a wall");
		return (0);
	}
	return (1);
}

static int	cub3d_validate_map(t_cub3d_scene *scene)
{
	int	i;

	if (!scene || !scene->map || scene->map_width <= 0
		|| scene->map_height <= 0)
	{
		cub3d_error("invalid map data");
		return (0);
	}
	i = 0;
	while (i < scene->map_height)
	{
		if (!scene->map[i])
		{
			cub3d_error("invalid map row");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	cub3d_validate_textures(t_cub3d_scene *scene)
{
	int	i;

	i = 0;
	while (i < CUB3D_TEX_COUNT)
	{
		if (!scene->textures[i])
		{
			cub3d_error("missing wall texture");
			return (0);
		}
		i++;
	}
	return (1);
}

int	cub3d_validate_scene(t_cub3d_scene *scene)
{
	if (!cub3d_validate_map(scene))
		return (0);
	if (!cub3d_validate_player(scene))
		return (0);
	if (!cub3d_validate_textures(scene))
		return (0);
	return (1);
}
