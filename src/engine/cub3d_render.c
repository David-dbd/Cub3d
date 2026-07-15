/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:35:24 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static void	cub3d_clear_frame(t_cub3d_engine *engine)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < engine->height)
	{
		if (y < engine->height / 2)
			color = engine->scene.ceiling_color;
		else
			color = engine->scene.floor_color;
		x = 0;
		while (x < engine->width)
		{
			cub3d_put_pixel(&engine->frame, x, y, color);
			x++;
		}
		y++;
	}
}

int	cub3d_render_frame(t_cub3d_engine *engine)
{
	int	x;

	cub3d_clear_frame(engine);
	x = 0;
	while (x < engine->width)
	{
		cub3d_cast_column(engine, x);
		x++;
	}
	mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	return (0);
}

int	cub3d_frame(void *param)
{
	t_cub3d_engine	*engine;

	engine = (t_cub3d_engine *)param;
	cub3d_update_player(engine);
	cub3d_render_frame(engine);
	return (0);
}

int	cub3d_engine_run(t_cub3d_engine *engine)
{
	if (!engine)
		return (1);
	mlx_hook(engine->win, CUB3D_EVENT_KEY_PRESS, CUB3D_MASK_KEY_PRESS,
		cub3d_key_press, engine);
	mlx_hook(engine->win, CUB3D_EVENT_KEY_RELEASE, CUB3D_MASK_KEY_RELEASE,
		cub3d_key_release, engine);
	mlx_hook(engine->win, CUB3D_EVENT_DESTROY, CUB3D_MASK_DESTROY,
		cub3d_close, engine);
	mlx_loop_hook(engine->mlx, cub3d_frame, engine);
	cub3d_render_frame(engine);
	mlx_loop(engine->mlx);
	return (0);
}
