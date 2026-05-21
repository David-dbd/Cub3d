/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:50:41 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/05/21 16:08:31 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/cub3d.h"

static void	validate_args(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) < 4
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		exit_error(NULL, WRONG_F, LOCAL_ERROR);
}

int	main(int argc, char **argv)
{
	t_game	the_game;

	the_game = (t_game){0};
	validate_args(argc, argv);
	parsing_engine(&the_game, argc, argv);
	configure_mlx_set_up();
	return (0);
}
