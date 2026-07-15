/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_ray_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:35:39 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static void	cub3d_pick_texture_id(t_cub3d_engine *engine,
		t_cub3d_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0.0)
		ray->tex_id = CUB3D_TEX_WE;
	else if (ray->side == 0)
		ray->tex_id = CUB3D_TEX_EA;
	else if (ray->ray_dir_y > 0.0)
		ray->tex_id = CUB3D_TEX_NO;
	else
		ray->tex_id = CUB3D_TEX_SO;
	if (ray->side == 0)
		ray->wall_x = engine->player.y + ray->perp_dist * ray->ray_dir_y;
	else
		ray->wall_x = engine->player.x + ray->perp_dist * ray->ray_dir_x;
}

static void	cub3d_pick_texture_x(t_cub3d_engine *engine,
		t_cub3d_ray *ray)
{
	t_cub3d_img	*texture;

	ray->wall_x -= floor(ray->wall_x);
	texture = &engine->textures[ray->tex_id];
	ray->tex_x = (int)(ray->wall_x * (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x < 0.0)
		ray->tex_x = texture->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0.0)
		ray->tex_x = texture->width - ray->tex_x - 1;
}

void	cub3d_pick_texture(t_cub3d_engine *engine, t_cub3d_ray *ray)
{
	cub3d_pick_texture_id(engine, ray);
	cub3d_pick_texture_x(engine, ray);
}
