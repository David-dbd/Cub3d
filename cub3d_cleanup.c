/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:50:41 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/14 10:47:09 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	validate_args(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) < 4
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		exit(print_error(WRONG_F, LOCAL_ERROR));
}

int	main(int argc, char **argv)
{
	t_game	the_game;
	t_cub3d_scene	scene;

	init_data(&the_game);
	validate_args(argc, argv);
	parsing_engine(&the_game, argv);
	build_scene(&the_game, &scene);
	cub3d_engine_start(&scene);
	free(scene.row_lengths);
	return (0);
}
