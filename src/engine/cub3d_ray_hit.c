/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_ray_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:35:45 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

void	cub3d_dda(t_cub3d_engine *engine, t_cub3d_ray *ray)
{
	while (cub3d_map_cell(engine, ray->map_x, ray->map_y) != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

void	cub3d_prepare_slice(t_cub3d_engine *engine, t_cub3d_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_dist < CUB3D_EPSILON)
		ray->perp_dist = CUB3D_EPSILON;
	ray->line_height = (int)(engine->height / ray->perp_dist);
	ray->draw_start = -ray->line_height / 2 + engine->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + engine->height / 2;
	if (ray->draw_end >= engine->height)
		ray->draw_end = engine->height - 1;
}
