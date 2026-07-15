/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:35:53 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static void	cub3d_try_move(t_cub3d_engine *engine, double step_x,
		double step_y)
{
	double	next_x;
	double	next_y;

	next_x = engine->player.x + step_x;
	next_y = engine->player.y + step_y;
	if (!cub3d_is_wall(engine, next_x, engine->player.y))
		engine->player.x = next_x;
	if (!cub3d_is_wall(engine, engine->player.x, next_y))
		engine->player.y = next_y;
}

static void	cub3d_rotate(t_cub3d_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

void	cub3d_update_player(t_cub3d_engine *engine)
{
	if (engine->input.forward)
		cub3d_try_move(engine, engine->player.dir_x * CUB3D_MOVE_SPEED,
			engine->player.dir_y * CUB3D_MOVE_SPEED);
	if (engine->input.backward)
		cub3d_try_move(engine, -engine->player.dir_x * CUB3D_MOVE_SPEED,
			-engine->player.dir_y * CUB3D_MOVE_SPEED);
	if (engine->input.strafe_left)
		cub3d_try_move(engine, engine->player.dir_y * CUB3D_MOVE_SPEED,
			-engine->player.dir_x * CUB3D_MOVE_SPEED);
	if (engine->input.strafe_right)
		cub3d_try_move(engine, -engine->player.dir_y * CUB3D_MOVE_SPEED,
			engine->player.dir_x * CUB3D_MOVE_SPEED);
	if (engine->input.turn_left)
		cub3d_rotate(&engine->player, -CUB3D_ROT_SPEED);
	if (engine->input.turn_right)
		cub3d_rotate(&engine->player, CUB3D_ROT_SPEED);
}

void	cub3d_set_player_direction(t_cub3d_player *player, char direction)
{
	player->dir_x = 0.0;
	player->dir_y = -1.0;
	if (direction == 'S')
		player->dir_y = 1.0;
	else if (direction == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
	else if (direction == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
	player->plane_x = -player->dir_y * CUB3D_PLANE_LEN;
	player->plane_y = player->dir_x * CUB3D_PLANE_LEN;
}
