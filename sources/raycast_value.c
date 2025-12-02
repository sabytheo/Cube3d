/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:35:08 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/02 15:32:02 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_raycast_values(t_game *cube, t_raycast *raycast, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	raycast->angle = cube->player.angle - atan(camera_x
			* cube->player.tan_fov_2);
	raycast->dir.x = cos(raycast->angle);
	raycast->dir.y = -sin(raycast->angle);
	raycast->deltadist_x = fabs(1 / raycast->dir.x);
	raycast->deltadist_y = fabs(1 / raycast->dir.y);
	raycast->int_x = (int)cube->player.pos_x;
	raycast->int_y = (int)cube->player.pos_y;
	raycast->float_x = cube->player.pos_x;
	raycast->float_y = cube->player.pos_y;
	raycast->start_y = HEIGHT * 0.5;
}

void	init_raycast_direction(t_game *cube, t_raycast *raycast)
{
	if (raycast->dir.x < 0)
	{
		raycast->step_x = -1;
		raycast->sidedist_x = (cube->player.pos_x - raycast->int_x)
			* raycast->deltadist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->sidedist_x = (raycast->int_x + 1.0 - cube->player.pos_x)
			* raycast->deltadist_x;
	}
	if (raycast->dir.y < 0)
	{
		raycast->step_y = -1;
		raycast->sidedist_y = (cube->player.pos_y - raycast->int_y)
			* raycast->deltadist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->sidedist_y = (raycast->int_y + 1.0 - cube->player.pos_y)
			* raycast->deltadist_y;
	}
}

void	get_distance_and_wallheight(t_game *cube, t_raycast *raycast, int side)
{
	if (side == 0)
		raycast->distance = (raycast->int_x - cube->player.pos_x + (1
					- raycast->step_x) / 2) / raycast->dir.x;
	else
		raycast->distance = (raycast->int_y - cube->player.pos_y + (1
					- raycast->step_y) / 2) / raycast->dir.y;
	cube->raycast.corrected_distance = cube->raycast.distance
		* cos(cube->raycast.angle - cube->player.angle);
	if (cube->raycast.corrected_distance <= 0)
		cube->raycast.corrected_distance = 0.1;
	cube->raycast.wall_height = (cube->raycast.base_height
			* cube->raycast.d_plan) / cube->raycast.corrected_distance;
}
