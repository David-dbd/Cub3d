/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:36:01 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

int	cub3d_image_new(t_cub3d_engine *engine, t_cub3d_img *img,
		int width, int height)
{
	img->ptr = mlx_new_image(engine->mlx, width, height);
	if (!img->ptr)
		return (0);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
	{
		cub3d_image_destroy(engine, img);
		return (0);
	}
	img->width = width;
	img->height = height;
	return (1);
}

void	cub3d_image_destroy(t_cub3d_engine *engine, t_cub3d_img *img)
{
	if (img->ptr)
		mlx_destroy_image(engine->mlx, img->ptr);
	cub3d_bzero(img, sizeof(t_cub3d_img));
}

void	cub3d_put_pixel(t_cub3d_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	cub3d_get_pixel(t_cub3d_img *img, int x, int y)
{
	char	*src;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	src = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)src);
}
