/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 01:19:00 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/14 00:24:06 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Function to exit the program safely. It frees the memory and detects the
	specific error from the project so that we can know.

	NOTE: Try to do the printf_fd so that it becomes more efficient
	
	FALTA LIMPIAR TODO. EL BOUNDS, TODOS LOS T_NAME QUE SEAN GENERADOS CON MALLOC
*/

static void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	free(map->lines);   // es un único bloque reallocado, no hay que iterar
	map->lines = NULL;
}

static void	free_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (config->path[i])
			free(config->path[i]);
		config->path[i] = NULL;
		i++;
	}
}

void	exit_error(t_game *the_game)
{
	if (the_game->fd >= 0)
		close(the_game->fd);
	if (the_game)
	{
		free_map(&the_game->map);
		free_config(&the_game->config);
	}
	exit(STDERR_FILENO);
}

int	print_error(char *error_message, int error_type)
{
	if (error_type == SYSTEM_CALL)
		perror("Error: ");
	else
		ft_putstr_fd(error_message, STDERR_FILENO);
	return (ERROR);
}