/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 00:00:00 by pestelle          #+#    #+#             */
/*   Updated: 2026/05/28 00:00:00 by pestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_private.h"

int	cub3d_engine_start(t_cub3d_scene *scene)
{
	t_cub3d_engine	*engine;

	engine = NULL;
	if (cub3d_engine_init(&engine, scene) != 0)
		return (1);
	cub3d_engine_run(engine);
	cub3d_engine_destroy(engine);
	return (0);
}
