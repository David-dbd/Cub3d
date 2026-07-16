/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/07/16 12:44:36 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PRIVATE_H
# define CUB3D_PRIVATE_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "cub3d_engine.h"
# include "cub3d.h"

# define CUB3D_EVENT_KEY_PRESS 2
# define CUB3D_EVENT_KEY_RELEASE 3
# define CUB3D_EVENT_DESTROY 17

# define CUB3D_MASK_KEY_PRESS 1L
# define CUB3D_MASK_KEY_RELEASE 2L
# define CUB3D_MASK_DESTROY 131072L

# define CUB3D_KEY_ESC 65307
# define CUB3D_KEY_W 119
# define CUB3D_KEY_A 97
# define CUB3D_KEY_S 115
# define CUB3D_KEY_D 100
# define CUB3D_KEY_LEFT 65361
# define CUB3D_KEY_RIGHT 65363

# define CUB3D_MAC_ESC 53
# define CUB3D_MAC_W 13
# define CUB3D_MAC_A 0
# define CUB3D_MAC_S 1
# define CUB3D_MAC_D 2
# define CUB3D_MAC_LEFT 123
# define CUB3D_MAC_RIGHT 124

# define CUB3D_MOVE_SPEED 0.055
# define CUB3D_ROT_SPEED 0.04
# define CUB3D_PLANE_LEN 0.66
# define CUB3D_EPSILON 0.000001

typedef struct s_cub3d_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_cub3d_img;

typedef struct s_cub3d_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_cub3d_player;

typedef struct s_cub3d_input
{
	int	forward;
	int	backward;
	int	strafe_left;
	int	strafe_right;
	int	turn_left;
	int	turn_right;
}	t_cub3d_input;

typedef struct s_cub3d_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_dist;
	double	wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_id;
	int		tex_x;
}	t_cub3d_ray;

struct s_cub3d_engine
{
	void			*mlx;
	void			*win;
	t_cub3d_img		frame;
	t_cub3d_img		textures[CUB3D_TEX_COUNT];
	t_cub3d_scene	scene;
	t_cub3d_player	player;
	t_cub3d_input	input;
	int				width;
	int				height;
};

void	cub3d_bzero(void *ptr, int size);
void	cub3d_error(char *message);
int		cub3d_validate_scene(t_cub3d_scene *scene);
void	cub3d_set_player_direction(t_cub3d_player *player, char direction);
char	cub3d_map_cell(t_cub3d_engine *engine, int x, int y);
int		cub3d_is_wall(t_cub3d_engine *engine, double x, double y);

int		cub3d_image_new(t_cub3d_engine *engine, t_cub3d_img *img,
			int width, int height);
void	cub3d_image_destroy(t_cub3d_engine *engine, t_cub3d_img *img);
void	cub3d_put_pixel(t_cub3d_img *img, int x, int y, int color);
int		cub3d_get_pixel(t_cub3d_img *img, int x, int y);
int		cub3d_load_textures(t_cub3d_engine *engine);
void	cub3d_destroy_textures(t_cub3d_engine *engine);

int		cub3d_render_frame(t_cub3d_engine *engine);
void	cub3d_init_ray(t_cub3d_engine *engine, t_cub3d_ray *ray, int x);
void	cub3d_dda(t_cub3d_engine *engine, t_cub3d_ray *ray);
void	cub3d_prepare_slice(t_cub3d_engine *engine, t_cub3d_ray *ray);
void	cub3d_pick_texture(t_cub3d_engine *engine, t_cub3d_ray *ray);
void	cub3d_draw_slice(t_cub3d_engine *engine, t_cub3d_ray *ray, int x);
void	cub3d_cast_column(t_cub3d_engine *engine, int x);
void	cub3d_update_player(t_cub3d_engine *engine);

int		cub3d_key_press(int keycode, void *param);
int		cub3d_key_release(int keycode, void *param);
int		cub3d_close(void *param);
int		cub3d_frame(void *param);

#endif
