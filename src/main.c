/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:50:41 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/06/19 00:55:53 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/cub3d.h"

static void	validate_args(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) < 4
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		exit(print_error(WRONG_F, LOCAL_ERROR));
}

int	main(int argc, char **argv)
{
	t_game	the_game;

	init_data(&the_game);
	validate_args(argc, argv);
	parsing_engine(&the_game, argv);
	//configure_mlx_set_up(&the_game);
	return (0);
}
