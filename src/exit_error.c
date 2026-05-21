/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 01:19:00 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/04/17 20:52:50 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/cub3d.h"

/*
	Function to exit the program safely. It frees the memory and detects the
	specific error from the project so that we can know.

	NOTE: Try to do the printf_fd so that it becomes more efficient
*/

void	exit_error(t_game *the_game)
{
	if (the_game)
		free (the_game);
	exit(STDERR_FILENO);
}

int	print_error(const char error_message, int error_type)
{
	if (error_type == SYSTEM_CALL)
		perror("Error: ");
	else
		ft_putstr_fd(error_message, STDERR_FILENO);
	return (ERROR);
}