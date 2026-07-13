/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:35:30 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

void	cub3d_cast_column(t_cub3d_engine *engine, int x)
{
	t_cub3d_ray	ray;

	cub3d_bzero(&ray, sizeof(t_cub3d_ray));
	cub3d_init_ray(engine, &ray, x);
	cub3d_dda(engine, &ray);
	cub3d_prepare_slice(engine, &ray);
	cub3d_pick_texture(engine, &ray);
	cub3d_draw_slice(engine, &ray, x);
}
