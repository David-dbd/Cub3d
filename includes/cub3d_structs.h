/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 23:16:24 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/17 12:50:44 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include "cub3d.h"

typedef struct s_rules
{
	int		player_counter;
	int		full_lines;
}	t_rules;

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
	int	line_start;
	int	line_end;
	int	line_type;
	int	line_counter;
}	t_line_data;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_line_data	*lines;
	int			global_start;
	int			global_end;
}	t_map;

typedef struct s_textures
{
	t_img	img;
	int		width;
	int		height;
}	t_textures;

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
