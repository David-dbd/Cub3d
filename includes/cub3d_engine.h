/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_engine.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/27 00:00:00 by pestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENGINE_H
# define CUB3D_ENGINE_H

# define CUB3D_DEFAULT_WIDTH 1280
# define CUB3D_DEFAULT_HEIGHT 720

# define CUB3D_TEX_NO 0
# define CUB3D_TEX_SO 1
# define CUB3D_TEX_WE 2
# define CUB3D_TEX_EA 3
# define CUB3D_TEX_COUNT 4

typedef struct s_cub3d_engine	t_cub3d_engine;

typedef struct s_cub3d_scene
{
	char	**map;
	int		*row_lengths;
	int		map_width;
	int		map_height;
	char	*textures[CUB3D_TEX_COUNT];
	int		floor_color;
	int		ceiling_color;
	double	player_x;
	double	player_y;
	char	player_dir;
	int		screen_width;
	int		screen_height;
}	t_cub3d_scene;

int		cub3d_engine_start(t_cub3d_scene *scene);
int		cub3d_engine_init(t_cub3d_engine **engine, t_cub3d_scene *scene);
int		cub3d_engine_run(t_cub3d_engine *engine);
void	cub3d_engine_destroy(t_cub3d_engine *engine);

#endif
