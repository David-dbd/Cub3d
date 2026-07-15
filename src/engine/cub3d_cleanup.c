/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 00:00:00 by pestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

void	cub3d_engine_destroy(t_cub3d_engine *engine)
{
	if (!engine)
		return ;
	if (engine->mlx)
	{
		cub3d_destroy_textures(engine);
		cub3d_image_destroy(engine, &engine->frame);
		if (engine->win)
			mlx_destroy_window(engine->mlx, engine->win);
		mlx_destroy_display(engine->mlx);
		free(engine->mlx);
	}
	free(engine);
}
