/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:41:10 by egache            #+#    #+#             */
/*   Updated: 2025/11/27 17:41:46 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_floor_and_ceil_tab(t_game *cube)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		cube->textures.ceiling[i] = -1;
		cube->textures.floor[i] = -1;
		i++;
	}
}

void	init_values(t_game *cube)
{
	cube->player.fov = M_PI / 3;
	cube->raycast.base_height = 1;
	cube->raycast.d_plan = WIDTH / (2 * tan(cube->player.fov * 0.5));
	cube->player.speed = 1;
	cube->player.rotation_speed = 1;
	cube->delta_time = 0.016;
	init_floor_and_ceil_tab(cube);
}
