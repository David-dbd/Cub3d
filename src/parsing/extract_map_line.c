/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 02:00:32 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/06/18 16:43:46 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"

int	extract_map_line(char **map_line, char *line)
{
	*map_line = ft_strdup(line); //maybe I should not copy the \n of each line
	if (!*map_line)
		return (print_error(NULL, SYSTEM_CALL));
	return (SUCCESS);
}
