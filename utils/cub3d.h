/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:50:47 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/04/22 22:44:33 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                              LIBRARIES                                     */
/* ************************************************************************** */

# include "cub3d_structs.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

/* ************************************************************************** */
/*                              MACROS                                        */
/* ************************************************************************** */

//RETURNS
# define ERROR								-1
# define SUCCESS							1

//ERROR TYPE
# define SYSTEM_CALL						2
# define LOCAL_ERROR						-2

//ERROR MESSAGES
# define WRONG_F							"Error: Wrong file\n"
# define WRONG_P							"Error: Wrong path\n"
# define WRONG_C							"Error: Wrong Colors\n"
# define WRONG_M							"Error: Wrong Map\n"
# define EMPTY_FILE							"Error: Empty file"
# define MLX_ISSUE							"Error: MLX failed\n"

//BOOL
# define TRUE								1
# define FALSE								0
# define MIDDLE_LINE						2
# define FULL_LINE							3


/* ************************************************************************** */
/*                              FUNCTIONS                                     */
/* ************************************************************************** */

#endif