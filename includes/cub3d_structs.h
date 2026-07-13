/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 23:16:24 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/14 00:13:49 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRCUTS_H
# define CUB3D_STRCUTS_H

#include "cub3d.h"

typedef struct s_rules
{
	int		player_counter;
	int		full_lines;
}	t_rules;

//saves the image ptr, the addres to the pixel buffer and info of the pixels
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	frame;
}	t_mlx;

typedef struct s_line_data
{
	int	line_start;// índice del primer carácter NO espacio
	int	line_end;// índice del último carácter NO espacio
	int	line_type;
	int	line_counter;
}	t_line_data;

typedef struct s_map
{
	char	**grid;	// matriz del mapa
	int		width;
	int		height;
	t_line_data	*lines;
	int		global_start; // sistema de referencia global
	int		global_end;
}	t_map;

//saves the ptr to the buffer that holds the actual image
typedef struct s_textures
{
	t_img	img;
	int		width;
	int		height;
}	t_textures;

//raw .cub data
typedef struct s_config
{
	char	*path[4];
	int		floor_color;
	int		ceiling_color;
}	t_config;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	start_dir;
}	t_player;

//core structurre
typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_textures	textures[4];
	t_config	config;
	int			fd;
}	t_game;

#endif
