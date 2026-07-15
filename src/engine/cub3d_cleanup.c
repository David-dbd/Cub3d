/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/07/15 11:11:44 by davdiaz-         ###   ########.fr       */
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
	parse_clean_up(engine->scene.the_game);
	free(engine->scene.row_lengths);
	free(engine);
}
