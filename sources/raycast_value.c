/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:35:08 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:48:15 by egache           ###   ########.fr       */
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
	raycast->deltaDistX = fabs(1 / raycast->dir.x);
	raycast->deltaDistY = fabs(1 / raycast->dir.y);
	raycast->intX = (int)cube->player.pos_x;
	raycast->intY = (int)cube->player.pos_y;
	raycast->floatX = cube->player.pos_x;
	raycast->floatY = cube->player.pos_y;
	raycast->start_y = HEIGHT * 0.5;
}

void	init_height_dplan(t_game *cube)
{
	cube->raycast.base_height = 1;
	cube->raycast.d_plan = WIDTH / (2 * tan(cube->player.fov * 0.5));
	return ;
}

void	init_raycast_direction(t_game *cube, t_raycast *raycast)
{
	if (raycast->dir.x < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (cube->player.pos_x - raycast->intX)
			* raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->intX + 1.0 - cube->player.pos_x)
			* raycast->deltaDistX;
	}
	if (raycast->dir.y < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (cube->player.pos_y - raycast->intY)
			* raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->intY + 1.0 - cube->player.pos_y)
			* raycast->deltaDistY;
	}
}

void	get_distance_and_wallheight(t_game *cube, t_raycast *raycast, int side)
{
	if (side == 0)
		raycast->distance = (raycast->intX - cube->player.pos_x + (1
					- raycast->stepX) / 2) / raycast->dir.x;
	else
		raycast->distance = (raycast->intY - cube->player.pos_y + (1
					- raycast->stepY) / 2) / raycast->dir.y;
	cube->raycast.corrected_distance = cube->raycast.distance
		* cos(cube->raycast.angle - cube->player.angle);
	if (cube->raycast.corrected_distance <= 0)
		cube->raycast.corrected_distance = 0.1;
	cube->raycast.wall_height = (cube->raycast.base_height
			* cube->raycast.d_plan) / cube->raycast.corrected_distance;
}
