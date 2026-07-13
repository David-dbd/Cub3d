/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:32:31 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/07/13 12:09:24 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	copy_path(t_game *the_game, char *path, int index)
{
	the_game->config.path[index] = ft_strdup(path);
	if (!the_game->config.path[index])
	{
		free (path);
		return (print_error(NULL, SYSTEM_CALL));
	}
	return (SUCCESS);
}

/*
	First we validate that there're only two words in the line (orient, path)
	Then we simply skip spaces and validate the orientation.
	Then we extract the path and check the lenght of the file. If it is
	greater than 5 (.xpm is 4) it implicitly means there's content before.
	Then we check the file extension and we try to open it.
*/

static int	open_and_compare(char *line,char *orientation, char **path)
{
	int		spaces_left;
	int		spaces_right;
	int		path_fd;
	int		path_len;

	spaces_left = 0;
	if (word_counter(line, 0) != 2)// "NO path.xpm hello bye.hello"
		return (print_error(WRONG_P, LOCAL_ERROR));
	spaces_left = ignore_spaces(line, 0, 0);
	if (ft_strncmp(line + spaces_left, orientation, 3) != 0) //we validate the ori.
		return (print_error(WRONG_P, LOCAL_ERROR));
	spaces_left = ignore_spaces(line, spaces_left + 3, 0); //from "NO "
	spaces_right = ignore_spaces(line, ft_strlen(line) - 1, 1);
	*path = ft_substr(line, spaces_left, spaces_right - spaces_left + 1);//we copy the path
	if (!*path)
		return (print_error(NULL, SYSTEM_CALL));
	path_len = ft_strlen(*path);
	if (path_len < 5
		|| ft_strncmp(*path + path_len - 4, ".xpm", 4) != 0)
		return (free(*path), print_error(WRONG_P, LOCAL_ERROR));
	if ((path_fd = open(*path, O_RDONLY)) == -1)
	{
		printf("fallo aqui!\n\n");
		return (free(*path), SYSTEM_CALL);
	}
	close(path_fd);
	return (SUCCESS);
}

int parse_paths(t_game *the_game, char *line, int index)
{
	char	*orientation[4] = {"NO ", "SO ", "WE ", "EA "};
	char	*path;
	int		error_track;

	error_track = open_and_compare(line, orientation[index], &path);
	if (error_track != SUCCESS)
		return (error_track);
	error_track = copy_path(the_game, path, index);
	if (error_track != SUCCESS)
		return (free(path), error_track);
	free(path);
	return (SUCCESS);
}

	/*
	while ((line = get_next_line(cub_fd)) != NULL && index < 4)
	{
		error_track = open_and_compare(line, orientation[index], &path);
		if (error_track != SUCCESS)
			return (error_track);
		error_track = copy_path(the_game, path, index);
		if (error_track != SUCCESS)
			return (free (line),free (path), error_track);
		free (line);
		free (path);
		line = NULL;
		index++;
	}
	if (!line && !index)
		return (print_error(EMPTY_FILE, LOCAL_ERROR));
	if (index != 4)//in case there wasnt all 4 lines
		return (free (line),free (path), print_error(WRONG_F, LOCAL_ERROR));
	return (SUCCESS);
	*/

