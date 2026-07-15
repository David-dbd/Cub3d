/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 00:00:00 by pestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static void	cub3d_apply_scene_defaults(t_cub3d_engine *engine)
{
	engine->width = engine->scene.screen_width;
	engine->height = engine->scene.screen_height;
	if (engine->width <= 0)
		engine->width = CUB3D_DEFAULT_WIDTH;
	if (engine->height <= 0)
		engine->height = CUB3D_DEFAULT_HEIGHT;
}

static int	cub3d_create_window(t_cub3d_engine *engine)
{
	engine->mlx = mlx_init();
	if (!engine->mlx)
	{
		cub3d_error("could not initialize MiniLibX");
		return (0);
	}
	engine->win = mlx_new_window(engine->mlx, engine->width, engine->height,
			"cub3D");
	if (!engine->win)
	{
		cub3d_error("could not create window");
		return (0);
	}
	if (!cub3d_image_new(engine, &engine->frame, engine->width,
			engine->height))
	{
		cub3d_error("could not create render image");
		return (0);
	}
	return (1);
}

static t_cub3d_engine	*cub3d_alloc_engine(void)
{
	t_cub3d_engine	*new_engine;

	new_engine = malloc(sizeof(t_cub3d_engine));
	if (!new_engine)
	{
		cub3d_error("malloc failed");
		return (NULL);
	}
	cub3d_bzero(new_engine, sizeof(t_cub3d_engine));
	return (new_engine);
}

static void	cub3d_setup_player(t_cub3d_engine *engine, t_cub3d_scene *scene)
{
	engine->player.x = scene->player_x;
	engine->player.y = scene->player_y;
	cub3d_set_player_direction(&engine->player, scene->player_dir);
}

int	cub3d_engine_init(t_cub3d_engine **engine, t_cub3d_scene *scene)
{
	t_cub3d_engine	*new_engine;

	if (!engine || !cub3d_validate_scene(scene))
		return (1);
	new_engine = cub3d_alloc_engine();
	if (!new_engine)
		return (1);
	new_engine->scene = *scene;
	cub3d_apply_scene_defaults(new_engine);
	cub3d_setup_player(new_engine, scene);
	if (!cub3d_create_window(new_engine) || !cub3d_load_textures(new_engine))
	{
		cub3d_engine_destroy(new_engine);
		return (1);
	}
	*engine = new_engine;
	return (0);
}
