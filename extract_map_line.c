/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 00:00:00 by pestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

static int	cub3d_load_texture(t_cub3d_engine *engine, int id, char *path)
{
	t_cub3d_img	*texture;

	texture = &engine->textures[id];
	texture->ptr = mlx_xpm_file_to_image(engine->mlx, path, &texture->width,
			&texture->height);
	if (!texture->ptr)
		return (0);
	texture->addr = mlx_get_data_addr(texture->ptr, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
	{
		cub3d_image_destroy(engine, texture);
		return (0);
	}
	if (texture->width <= 0 || texture->height <= 0)
	{
		cub3d_image_destroy(engine, texture);
		return (0);
	}
	return (1);
}

int	cub3d_load_textures(t_cub3d_engine *engine)
{
	int	i;

	i = 0;
	while (i < CUB3D_TEX_COUNT)
	{
		if (!cub3d_load_texture(engine, i, engine->scene.textures[i]))
		{
			cub3d_error("could not load XPM texture");
			cub3d_destroy_textures(engine);
			return (0);
		}
		i++;
	}
	return (1);
}

void	cub3d_destroy_textures(t_cub3d_engine *engine)
{
	int	i;

	i = 0;
	while (i < CUB3D_TEX_COUNT)
	{
		cub3d_image_destroy(engine, &engine->textures[i]);
		i++;
	}
}
