/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_ray_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:35:48 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static int	cub3d_texture_y(t_cub3d_img *texture, double tex_pos)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}

void	cub3d_draw_slice(t_cub3d_engine *engine, t_cub3d_ray *ray, int x)
{
	t_cub3d_img	*texture;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			y;

	texture = &engine->textures[ray->tex_id];
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - engine->height / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = cub3d_texture_y(texture, tex_pos);
		cub3d_put_pixel(&engine->frame, x, y,
			cub3d_get_pixel(texture, ray->tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}
