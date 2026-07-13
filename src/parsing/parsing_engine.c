/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 01:01:27 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/14 00:23:45 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	The order for the orientation arr is: NO, SO, WE, EA
	The order for the colors are: F, C
	Everytime we match a line with the orientation or color we change the
	index from 1 to 0. This way, if there was a case of NO, NO, EA, EA, instead
	of evaluating those lines later, we check that the flag == 1. If not, we
	know is a duplicate
*/

void parsing_engine(t_game *the_game, char **argv)
{
	the_game->fd = open(argv[1], O_RDONLY);
	if (the_game->fd == -1)
		exit_error(the_game);
	if (figure_sections(the_game, the_game->fd) != SUCCESS)
		exit_error(the_game);
	if (parse_map(the_game, the_game->fd) != SUCCESS)//we leave the map as it is
		exit_error(the_game);
	close(the_game->fd);
	the_game->fd = -1;
	start_search_system(the_game);
	fill_out_player(the_game);
}
