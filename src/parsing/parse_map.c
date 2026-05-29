/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:39:06 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/05/29 01:51:56 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/cub3d.h"

/*
	Detects a wall is always 1's and counts it. There should always be 2 full_l
*/

static int	is_full_line(char *line, int *full_lines)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1')
			return (FALSE);
		i++;
	}
	*full_lines += 1;
	return (TRUE);
}

/*
	Detects a middle_line. Checks that always has 1's or 0's. If not, it checks
	for player postion. It detects when there's more than 1 letter per line.
	Also checks that starts in 1 and closes in 1. 
	If a line is already full then we return
*/

static int	is_middle_line(char *line, int *full_lines, int line_type, int *player_count)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (line_type == FULL_LINE || (line_type == FALSE && *full_lines == 0))
		return (FALSE);
	while (line[i] != '\0')
	{
		if ((i == 0 && line[i] != '1') || (i == len - 1 && line[i] != '1'))
			return (FALSE);
		if ((i > 0 && i < len - 1) && (line[i] != '0' && line[i] != '1'))
		{
			if (line[i] != 'N' && line[i] != 'E' && line[i] != 'S' && line[i] != 'W')
				return (FALSE);
			else
			{
				if (*player_count == 1)
					return (FALSE);
				(*player_count)++;
			}
		}
		i++;
	}
	return (TRUE);
}

/*
	Detects whether a line is full (111) or middle line. It uses line_type as
	a flag to know what line of the is. If it is a full line, then is_middle_line
	will detect it and wont change its state. The full_lines counter is another
	layer of valdiation. It should be 2 at the end of the process (first and last line).
	If the line_ryoe ends up being FALSE it means the line of the map we just
	read is wrong
*/

static int	examine_line(char **map_line, int *full_lines, int *player_count)
{
	int	line_type;

	line_type = FALSE; //ignore_spaces
	if (is_full_line(*map_line, full_lines))
		line_type = FULL_LINE;
	else if (is_middle_line(*map_line, full_lines, line_type, player_count))
		line_type = MIDDLE_LINE;
	if (line_type == FALSE)
		return (print_error(WRONG_M, LOCAL_ERROR));
	return (SUCCESS);
}

static int	extract_map_line(char **map_line, char *line)
{
	int	spaces_at_left;
	int	spaces_at_right;
	int	line_len;

	spaces_at_left = 0;
	if (word_counter(line, 0) != 1)// "111 111 111" pero verificar esto porque si que podría ser asi en algunos casos
		return (print_error(WRONG_P, LOCAL_ERROR));
	spaces_at_left = ignore_spaces(line, 0, 0);
	spaces_at_right = ignore_spaces(line, ft_strlen(line) - 1, 1);
	*map_line = ft_substr(line, spaces_at_left, ft_strlen(line) - spaces_at_right);
	if (!*map_line)
		return (print_error(NULL, SYSTEM_CALL));
	line_len = ft_strlen(*map_line);
	if (line_len < 3) //at least 111
		return (print_error(WRONG_P, LOCAL_ERROR));
	return (SUCCESS);
}

int	parse_map(t_game *the_game, int fd)
{
	char	*line;
	int		full_lines;
	int		index;
	int		player_counter;

	index = 0;
	full_lines = 0;
	player_counter = 0;
	line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (add_slot_arr(&the_game->map.grid, index) == ERROR)
			return (free(line), ERROR);
		if (extract_map_line(&the_game->map.grid[index], line) == ERROR)
			return (free(line), ERROR);
		if (examine_line(&the_game->map.grid[index], &full_lines, &player_counter) == ERROR)
			return (free(line), ERROR);
		free (line);
		index++;
	}
	if (full_lines != 2 || player_counter != 1)
		return (free (line), print_error(WRONG_M, LOCAL_ERROR));
	if (calculate_width_height(&the_game->map) == ERROR)
		return (free (line), print_error(WRONG_M, LOCAL_ERROR));
	return (SUCCESS);
}


/*
	La idea es muy sencilla: Itero sobre el mapa buscando espacios. Si encuentro un espacio, verifico las 4 direciones: derecha, izquierda,
	arriba y abajo. La idea es que hayan 1's en cada una de ellas (dependiendo del contexto). Esto hace que el espacio sea valido. La manera
	en la que se comprueba es muy sencilla, se verifican las mismas posiciones del index del espacio en las linea de arriba y abajo, derecha
	e izquierda hasta encontrar un 0 (no sería valido el mapa), un 1 (sería valido el mapa) o mas espacios (dependiendo del contexto es valido).
	Ahora bien, aunque se verifican las 4 direcciones, con solo tener 3 direcciones validas es suficiente para que el mapa sea valido. De esas 3,
	la derecha e izquierda SIEMPRE tienen que ser validas (porque en teoria una linea debe ser contenida en 1's), lo cual deja la opción 
	de arriba o abajo. Si por ejemplo, derecha, izquierda y arriba estan bien, igual se verifica abajo; Por alguna razón solo hay espacios, lo cual
	podría querer decir que es el final del mapa, con lo cual no esta mal. Sin embargo, si hubiese un 0, si estaria mal, y aunque las otras 3
	estuviensen bien, un espacio nunca puede estar rodeado de 0(s).

	En el parseo del mapa estoy pensando que cuando haya espacios en una linea pero que arriba de esa linea este cerrado con 1, por ejemplo: 
"100011001
11111    1111"
Para verificar si es valido, simplemente cuando llegue a la linea que contiene espacios hago un sistema que verifique la linea anterior en 
el mismo index del espacio, de modo que si encuentro un 1, entonces lo doy por bien visto, sigo con el siguiente espacio y vuelvo a verificar 
la linea de arriba en el siguiente index. Asi hasta que haya pasado sobre los espacios. Si por alguna razon me encuentro mas espacios, entonces
 sigo buscando una linea anterior (de una en una hasta hayar 1 o 0). Si la primera linea que encuentre tiene 0's en el mismo index que los espacios
  entonces lo reconozco como un error del mapa porque tiene una fuga.

Lo que quiero decir es que al menos tres direcciones deben ser correctas por regla general. Sin embargo, hay otra regla, y es que dos de esas 
direcciones TIENEN que ser derecha e izquierda. Es decir, si las tres direcciones validas terminan siendo arriba, derecha y abajo, eso estaria 
mal, ya que se necesitan que las direcciones laterales sean validas ya que cada linea del mapa deberia de estar contenida en 1 al menos al inicio 
y al final. Esto quiere decir que no necesariamente se necesitan verificar las 4 direcciones porque habran casos en los que arriba o abajo no seran
 validas pero eso no quiere decir que esten mal. Por ejmplo:
"1111111111
100011001
111111  11111"
En este ejemplo la direccion de abajo del espacio no es valida porque no hay nada, pero eso no quiere decir que el mapa sea invalido. De hecho el mapa ES VALIDO en este caso.



111111 ->INVALIDO (se encuentra un 0)
1    1
10   1
111111

111111 ->INVALIDO (se encuentra un 0)
1    1
1  0 1
1    1
111111

111111111111 ->VALIDO (encuentra solo 1's a su alrededor)
1          1
1   11111  1
1   10001  1
1   10001  1
1   11111  1
111111111111

11111111111111111111111111111 ->VALIDO (los espacios encuentran 1's. Aunque la direccion SUR esolo encuentra espacios, mientras no encuentren 0's)
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111


Reglas basicas:
1. La primera y u´ltima linea deben ser 1's (pueden tener espacios entre ellas siempre y cuando otras lineas cierren esos espacios)
2. Debe haber un caracter para el jugador - Se considera como un 0 (psición jugable)
3. Deber haber almenos un 0 (y/o un caracter). Si hay 2 o mas, pueden estar separados por 1's pero no espacios.



Estoy pensando en verificar primero que cada linea del mapa sea valida en terminos de saber si esta cerrada o no:
Luego, si la linea es valida (Full_line o middle_line), entonces la guardo tal cual (esta vez sin eliminar espacios). 
Y asi voy linea a linea. Si al final del dia todo era valido entonces guardare el mapa tal cual me lo dio el usuario.
 Luego, duplicare ese mapa: tendre el original y la copia la editare para normalizar. Cuando normalize, aplicare mi sistema 
 de validacion direccional que podrá ser aplicado sobre los espacios del mapa y no sobre los espacios exteriores. Si todo esta 
 bien, entonces utilizo el mapa original para la mlx. Podría eliminar la copia editada sin espacios luego de eso o podría almacenar
 la si la llegase a necesitar en el futuro, da igual por ahora
*/