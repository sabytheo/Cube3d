/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:26:36 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/02 15:32:02 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

void	get_distance_and_wallheight(t_game *cube, t_raycast *raycast)
{
	raycast->corrected_distance = raycast->distance * cos(raycast->angle
			- cube->player.angle);
	if (raycast->corrected_distance <= 0)
		raycast->corrected_distance = 0.1;
	raycast->wall_height = (raycast->base_height * raycast->d_plan)
		/ raycast->corrected_distance;
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

int	init_hit_char(t_map *map, t_raycast *raycast,
		t_hit_info **new_hit)
{
	int	side;

	if (raycast->sidedist_x < raycast->sidedist_y)
	{
		raycast->sidedist_x += raycast->deltadist_x;
		raycast->int_x += raycast->step_x;
		side = 0;
	}
	else
	{
		raycast->sidedist_y += raycast->deltadist_y;
		raycast->int_y += raycast->step_y;
		side = 1;
	}
	*new_hit = malloc(sizeof(t_hit_info));
	if (!*new_hit)
		return (-1);
	(*new_hit)->hit_type = map->final_grid[raycast->int_y][raycast->int_x];
	return (side);
}
