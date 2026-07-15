/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_ray_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:35:42 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static double	cub3d_ray_delta(double ray_dir)
{
	if (fabs(ray_dir) < CUB3D_EPSILON)
		return (1e30);
	return (fabs(1.0 / ray_dir));
}

static void	cub3d_init_ray_dir(t_cub3d_engine *engine,
		t_cub3d_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)engine->width - 1.0;
	ray->ray_dir_x = engine->player.dir_x
		+ engine->player.plane_x * ray->camera_x;
	ray->ray_dir_y = engine->player.dir_y
		+ engine->player.plane_y * ray->camera_x;
	ray->map_x = (int)engine->player.x;
	ray->map_y = (int)engine->player.y;
	ray->delta_dist_x = cub3d_ray_delta(ray->ray_dir_x);
	ray->delta_dist_y = cub3d_ray_delta(ray->ray_dir_y);
}

static void	cub3d_init_ray_x(t_cub3d_engine *engine, t_cub3d_ray *ray)
{
	if (ray->ray_dir_x < 0.0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (engine->player.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - engine->player.x)
			* ray->delta_dist_x;
	}
}

static void	cub3d_init_ray_y(t_cub3d_engine *engine, t_cub3d_ray *ray)
{
	if (ray->ray_dir_y < 0.0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (engine->player.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - engine->player.y)
			* ray->delta_dist_y;
	}
}

void	cub3d_init_ray(t_cub3d_engine *engine, t_cub3d_ray *ray, int x)
{
	cub3d_init_ray_dir(engine, ray, x);
	cub3d_init_ray_x(engine, ray);
	cub3d_init_ray_y(engine, ray);
}
