/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:33:01 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:48:48 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	if_wall_hit(t_game *cube, t_raycast *raycast, int side)
{
	if (!side)
	{
		raycast->floatX = cube->player.pos_x + raycast->dir.x
			* (raycast->sideDistX - raycast->deltaDistX);
		raycast->floatY = cube->player.pos_y + raycast->dir.y
			* (raycast->sideDistX - raycast->deltaDistX);
		cube->textures.x = raycast->floatY - floor(raycast->floatY);
	}
	else
	{
		raycast->floatX = cube->player.pos_x + raycast->dir.x
			* (raycast->sideDistY - raycast->deltaDistY);
		raycast->floatY = cube->player.pos_y + raycast->dir.y
			* (raycast->sideDistY - raycast->deltaDistY);
		cube->textures.x = raycast->floatX - floor(raycast->floatX);
	}
	return (side);
}
static int	ray_displacement(t_game *cube, t_raycast *raycast)
{
	int		side;
	bool	hit;

	hit = false;
	while (hit == false)
	{
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
		if (cube->map.final_grid[raycast->intY][raycast->intX] == '1')
		{
			hit = false;
			return (if_wall_hit(cube, raycast, side));
		}
	}
	return (0);
}

static t_img	*assign_texture_and_render(t_texture *textures,
		t_raycast *raycast, int side)
{
	if (raycast->dir.x > 0 && side == 0)
	{
		textures->y = textures->EA_img.ht / raycast->wall_height;
		textures->x = 1 - textures->x;
		return (&textures->EA_img);
	}
	else if (raycast->dir.x < 0 && side == 0)
	{
		textures->y = textures->WE_img.ht / raycast->wall_height;
		return (&textures->WE_img);
	}
	else if (raycast->dir.y > 0 && side == 1)
	{
		textures->y = textures->NO_img.ht / raycast->wall_height;
		return (&textures->NO_img);
	}
	else if (raycast->dir.y < 0 && side == 1)
	{
		textures->y = textures->SO_img.ht / raycast->wall_height;
		textures->x = 1 - textures->x;
		return (&textures->SO_img);
	}
	else
		return (NULL);
}

void	raycast(t_game *cube, t_raycast *raycast)
{
	int		x;
	int		side;
	t_img	*texture;

	texture = NULL;
	init_height_dplan(cube);
	side = 0;
	x = 0;
	while (x <= WIDTH)
	{
		init_raycast_values(cube, raycast, x);
		init_raycast_direction(cube, raycast);
		side = ray_displacement(cube, raycast);
		get_distance_and_wallheight(cube, raycast, side);
		texture = assign_texture_and_render(&cube->textures, raycast, side);
		render_wall(raycast->wall_height, cube, x, texture);
		x++;
	}
	return ;
}
