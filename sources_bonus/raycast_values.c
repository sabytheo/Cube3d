/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:26:36 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/19 20:18:15 by egache           ###   ########.fr       */
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
	raycast->deltaDistX = fabs(1 / raycast->dir.x);
	raycast->deltaDistY = fabs(1 / raycast->dir.y);
	raycast->intX = (int)cube->player.pos_x;
	raycast->intY = (int)cube->player.pos_y;
	raycast->floatX = cube->player.pos_x;
	raycast->floatY = cube->player.pos_y;
	raycast->start_y = HEIGHT * 0.5;
}

// void	init_height_dplan(t_game *cube, t_raycast *raycast)
// {
// 	raycast->base_height = 1;
// 	raycast->d_plan = WIDTH / (2 * tan(cube->player.fov * 0.5));
// 	return ;
// }

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

int	init_hit_char(t_map *map, t_raycast *raycast,
		t_hit_info **new_hit)
{
	int	side;

	if (raycast->sideDistX < raycast->sideDistY)
	{
		raycast->sideDistX += raycast->deltaDistX;
		raycast->intX += raycast->stepX;
		side = 0;
	}
	else
	{
		raycast->sideDistY += raycast->deltaDistY;
		raycast->intY += raycast->stepY;
		side = 1;
	}
	*new_hit = malloc(sizeof(t_hit_info));
	if (!*new_hit)
		return (-1);
	(*new_hit)->hit_type = map->final_grid[raycast->intY][raycast->intX];
	return (side);
}
