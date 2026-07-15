/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_search_system.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:19:20 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/15 10:49:46 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	Here we recieve the context of the space as well as the ptr to the space
	(to keep going through). We send it to each search function to find if
	it's valid or not. FALTARIA VALIDAR SI FALLA ABAJO, PUEDE FUNCIONAR SI 
	ARRIBA ESTA BIEN, O AL CONTRARIO. NO TIENE QUE SER UN ERROR
*/

static int	search_engine(t_game *g, int line_index, int space_in, int context)
{
	if (search_left(&g->map, line_index, space_in, context) == ERROR)
		return (print_error(WRONG_M, LOCAL_ERROR));
	if (search_right(&g->map, line_index, space_in, context) == ERROR)
		return (print_error(WRONG_M, LOCAL_ERROR));
	if (search_top(&g->map, space_in, 
		&g->map.lines[line_index], context) == ERROR)
		return (print_error(WRONG_M, LOCAL_ERROR));
	if (search_bottom(&g->map, space_in, 
		&g->map.lines[line_index], context) == ERROR)
		return (print_error(WRONG_M, LOCAL_ERROR));
	return (SUCCESS);
}

static int	figure_conte(t_game *g, int space_i, t_line_data bounds, int line_i)
{
	int	context;

	context = FALSE;
	if (space_i > bounds.line_start && space_i < bounds.line_end)
		context = INSIDE_SPACE;
	else if (space_i > bounds.line_start && space_i > bounds.line_end)
		context = OUTSIDE_SPACE_RIGHT;
	else if (space_i < bounds.line_start && space_i < bounds.line_end)
		context = OUTSIDE_SPACE_LEFT;
	if (search_engine(g, line_i, space_i, context) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	search_system_engine(t_game *the_game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (the_game->map.grid[row] != NULL)
	{
		col = 0;
		while (the_game->map.grid[row][col] != '\0')
		{
			if (the_game->map.grid[row][col] == ' ' 
				|| the_game->map.grid[row][col] == '\t')
			{
				if (figure_conte(the_game, col, 
					the_game->map.lines[row], row) == ERROR)
					exit_error(the_game);
			}
			col++;
		}
		row++;
	}
}
