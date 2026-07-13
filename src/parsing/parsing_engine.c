/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 01:01:27 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/13 11:36:19 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	close_error(int fd)
{
	close(fd);
	exit(STDERR_FILENO);
	//exit_error(the_game);
}

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
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error(the_game);
	if (figure_sections(the_game, fd) != SUCCESS)
		close_error(fd);
	if (parse_map(the_game, fd) != SUCCESS)//we leave the map as it is
		close_error(fd);
	close(fd);
	start_search_system(the_game);
	//fill_out_player(the_game); we CANT do that yet because we dont know if the map is valid yet
}
