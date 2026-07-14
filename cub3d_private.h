/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 00:00:00 by pestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static int	cub3d_is_key(int keycode, int linux_key, int mac_key)
{
	return (keycode == linux_key || keycode == mac_key);
}

static void	cub3d_set_key(t_cub3d_input *input, int keycode, int value)
{
	if (cub3d_is_key(keycode, CUB3D_KEY_W, CUB3D_MAC_W))
		input->forward = value;
	else if (cub3d_is_key(keycode, CUB3D_KEY_S, CUB3D_MAC_S))
		input->backward = value;
	else if (cub3d_is_key(keycode, CUB3D_KEY_A, CUB3D_MAC_A))
		input->strafe_left = value;
	else if (cub3d_is_key(keycode, CUB3D_KEY_D, CUB3D_MAC_D))
		input->strafe_right = value;
	else if (cub3d_is_key(keycode, CUB3D_KEY_LEFT, CUB3D_MAC_LEFT))
		input->turn_left = value;
	else if (cub3d_is_key(keycode, CUB3D_KEY_RIGHT, CUB3D_MAC_RIGHT))
		input->turn_right = value;
}

int	cub3d_key_press(int keycode, void *param)
{
	t_cub3d_engine	*engine;

	engine = (t_cub3d_engine *)param;
	if (cub3d_is_key(keycode, CUB3D_KEY_ESC, CUB3D_MAC_ESC))
		return (cub3d_close(engine));
	cub3d_set_key(&engine->input, keycode, 1);
	return (0);
}

int	cub3d_key_release(int keycode, void *param)
{
	t_cub3d_engine	*engine;

	engine = (t_cub3d_engine *)param;
	cub3d_set_key(&engine->input, keycode, 0);
	return (0);
}

int	cub3d_close(void *param)
{
	t_cub3d_engine	*engine;

	engine = (t_cub3d_engine *)param;
	mlx_loop_end(engine->mlx);
	return (0);
}
