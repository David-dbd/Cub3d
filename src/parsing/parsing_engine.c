/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 01:01:27 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/06/18 17:23:19 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"

static	void	close_error(int fd)
{
	close(fd);
	exit(STDERR_FILENO);
	//exit_error(the_game);
}

void parsing_engine(t_game *the_game, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error(the_game);
	if (parse_paths(the_game, fd) != SUCCESS)
		close_error(fd);
	if (parse_colors(the_game, fd) != SUCCESS)
		close_error(fd);
	if (parse_map(the_game, fd) != SUCCESS)//we leave the map as it is
		close_error(fd);
	close(fd);
	start_search_system(the_game);
	//if (the_game->game_mode == 1)
	//{
	//	if (parse_map_basic(the_game, fd) != SUCCESS)//we leave the map as it is
	//		close_error(the_game, fd);
	//}
	//else if (the_game->game_mode == 2)//we edit the map to make it work
	//{
	//	if (parse_map_premium(the_game, fd) != SUCCESS)
	//		close_error(the_game, fd);
	//}
	//fill_out_player(the_game); we CANT do that yet because we dont know if the map is valid yet
}
