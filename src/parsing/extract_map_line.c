/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 02:00:32 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/14 10:42:17 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	extract_map_line(char **map_line, char *line)
{
	*map_line = ft_strdup(line);
	if (!*map_line)
		return (print_error(NULL, SYSTEM_CALL));
	return (SUCCESS);
}
