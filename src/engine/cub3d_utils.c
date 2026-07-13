/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 17:36:25 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

void	cub3d_bzero(void *ptr, int size)
{
	unsigned char	*bytes;
	int				i;

	bytes = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		bytes[i] = 0;
		i++;
	}
}

void	cub3d_error(char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
		i++;
	write(2, "Error\n", 6);
	write(2, message, i);
	write(2, "\n", 1);
}

char	cub3d_map_cell(t_cub3d_engine *engine, int x, int y)
{
	char	cell;

	if (x < 0 || y < 0 || y >= engine->scene.map_height)
		return ('1');
	if (engine->scene.row_lengths && x >= engine->scene.row_lengths[y])
		return ('1');
	if (!engine->scene.row_lengths && x >= engine->scene.map_width)
		return ('1');
	cell = engine->scene.map[y][x];
	if (cell == '\0' || cell == ' ')
		return ('1');
	return (cell);
}

int	cub3d_is_wall(t_cub3d_engine *engine, double x, double y)
{
	return (cub3d_map_cell(engine, (int)x, (int)y) == '1');
}
