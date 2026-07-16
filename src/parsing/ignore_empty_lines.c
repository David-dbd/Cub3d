/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_empty_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 00:36:54 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/16 14:19:08 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ignore_empty_lines(char *line, int fd)
{
	while (line && is_empty_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
