/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_mlx_set_up.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:48:57 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/05/27 15:14:23 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/cub3d.h"

static int	set_up_textures(t_game *the_game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		the_game->textures[i] = mlx_xpm_file_to_image(the_game->mlx.mlx,
			the_game->config.path[i], &the_game->textures[i].width,
			&the_game->textures[i].height);
		if (!&the_game->textures[i].img)
			return (print_error(MLX_ISSUE, LOCAL_ERROR));
		the_game->textures[i].img.addr = mlx_get_data_addr(the_game->textures[i].img, &the_game->textures[i].img.bpp,
			&the_game->textures[i].img.line_len, &the_game->textures[i].img.endian);
		i++;
	}
}

int	configure_mlx_set_up(t_game *the_game)
{
	mlx_init();
	the_game->mlx.win = mlx_new_window();
	if (set_up_textures(the_game) == ERROR)
		exit_error(the_game);
}