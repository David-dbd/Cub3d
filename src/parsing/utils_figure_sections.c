/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_figure_sections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 19:01:31 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/16 14:19:24 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	get_path_index(char *line)
{
	if (ft_charstr_match(line, "NO "))
		return (0);
	if (ft_charstr_match(line, "SO "))
		return (1);
	if (ft_charstr_match(line, "WE "))
		return (2);
	if (ft_charstr_match(line, "EA "))
		return (3);
	return (-1);
}

int	get_color_index(char *line)
{
	if (ft_charstr_match(line, "F "))
		return (0);
	if (ft_charstr_match(line, "C "))
		return (1);
	return (-1);
}
