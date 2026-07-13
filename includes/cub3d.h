/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:50:47 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/13 11:35:40 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                              LIBRARIES                                     */
/* ************************************************************************** */

# include "cub3d_structs.h"
# include "cub3d_engine.h"
# include "../lib/libft_plus/libft_plus.h"
//# include "../lib/libft_plus/ft_printf_fd.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

/* ************************************************************************** */
/*                              MACROS                                        */
/* ************************************************************************** */

//RETURNS
# define ERROR								-1
# define SUCCESS							1
# define IGNORE								2

//ERROR TYPE
# define SYSTEM_CALL						2
# define LOCAL_ERROR						-2

//ERROR MESSAGES
# define WRONG_F							"\033[1;31mError: Wrong file\033[0m\n\n"
# define WRONG_P							"\033[1;31mError: Wrong path\033[0m\n\n"
# define WRONG_C							"\033[1;31mError: Wrong Colors\033[0m\n\n"
# define WRONG_M							"\033[1;31mError: Wrong Map\033[0m\n\n"
# define INVALID_C							"\033[1;31mError: Invalid Content\033[0m\n\n"
# define EMPTY_FILE							"\033[1;31mError: Empty file\033[0m\n\n"
# define MLX_ISSUE							"\033[1;31mError: MLX failed\033[0m\n\n"

//BOOL
# define TRUE								1
# define FALSE								0
# define MIDDLE_LINE						2
# define TOP_LINE							3
# define BOTTOM_LINE						4
# define INSIDE_SPACE						5
# define OUTSIDE_SPACE_RIGHT				6
# define OUTSIDE_SPACE_LEFT					7
# define PATH_LINE							8
# define COLOR_LINE							9


/* ************************************************************************** */
/*                              FUNCTIONS                                     */
/* ************************************************************************** */

//parsing
void	parsing_engine(t_game *the_game, char **argv);
int		figure_sections(t_game *the_game, int cub_fd);
int		parse_paths(t_game *the_game, char *line, int index);
int		parse_map(t_game *the_game, int fd);
int		parse_colors(t_game *the_game, char *line, int index);
void	fill_out_player(t_game *the_game);
int		extract_map_line(char **map_line, char *line);

//utils
int	calculate_width_height(t_map *map);
int	add_slot(char ***map, t_line_data **lines, int index);
int	word_counter(char *line, int start);
int	ignore_spaces(char *line, int k, int direction);
int	get_path_index(char *line);
int	get_color_index(char *line);
int	check_colors_range(int r, int g, int b);

//search_engine
void	start_search_system(t_game *the_game);
void	search_system_engine(t_game *the_game);
int		search_left(t_map *map, int line_index, int space_index, int context);
int		search_right(t_map *map, int line_index, int space_index, int context);
int		search_top(t_map *map, int space_index, t_line_data *lines, int context);
int		search_bottom(t_map *map, int space_index, t_line_data *lines, int context);


//error
int		print_error(char *error_message, int error_type);
void	exit_error(t_game *the_game);

//init_data
void	init_data(t_game *the_game);
//int configure_mlx_set_up(t_game *the_game);

int	build_scene(t_game *the_game, t_cub3d_scene *scene);

#endif