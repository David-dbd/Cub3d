/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_search_system.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:19:20 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/11 19:10:00 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"

/*
	Here we recieve the context of the space as well as the ptr to the space
	(to keep going through). We send it to each search function to find if
	it's valid or not. FALTARIA VALIDAR SI FALLA ABAJO, PUEDE FUNCIONAR SI ARRIBA ESTA BIEN, O AL CONTRARIO. NO TIENE QUE SER UN ERROR
*/

static int	search_engine(t_game *the_game, int line_index, int space_index, int context)
{
	if (search_left(&the_game->map, line_index, space_index, context) == ERROR)
		return (print_error("ERROR EN ORIENT", LOCAL_ERROR));
	if (search_right(&the_game->map, line_index, space_index, context) == ERROR) //un if dentro de cada uno para omitirlo si es cierto conexto
		return (print_error("ERROR EN ORIENT", LOCAL_ERROR));
	if (search_top(&the_game->map, space_index, &the_game->map.lines[line_index], context) == ERROR)
		return (print_error("ERROR EN ORIENT", LOCAL_ERROR));
	if (search_bottom(&the_game->map, space_index, &the_game->map.lines[line_index], context) == ERROR)
		return (print_error("ERROR EN ORIENT", LOCAL_ERROR));
	return (SUCCESS);
}

static int	figure_context(t_game *the_game, int space_index, t_line_data bounds, int line_index)
{
	int	context;

	context = FALSE;
	if (space_index > bounds.line_start && space_index < bounds.line_end)
		context = INSIDE_SPACE;
	else if (space_index > bounds.line_start && space_index > bounds.line_end)
		context = OUTSIDE_SPACE_RIGHT;
	else if (space_index < bounds.line_start && space_index < bounds.line_end)
		context = OUTSIDE_SPACE_LEFT;
	if (search_engine(the_game, line_index, space_index, context) == ERROR)
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
				if (figure_context(the_game, col, the_game->map.lines[row], row) == ERROR) //comparamos el index del espacio actual (col) vs el start y end reales de la linea. No enviamos el [row][col] porque eso es un char y un un index //pasamos el index y el str ya que si pasamos el index como ptr solo podemos acceder a lo que se encuentra despues y no antes
					exit_error(the_game);
			}
			col++;
		}
		row++;
	}
}
