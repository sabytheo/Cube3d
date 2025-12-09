/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:33:01 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/09 17:48:29 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	if_wall_hit(t_game *cube, t_raycast *raycast, int side)
{
	if (!side)
	{
		raycast->float_x = cube->player.pos_x + raycast->dir.x
			* (raycast->sidedist_x - raycast->deltadist_x);
		raycast->float_y = cube->player.pos_y + raycast->dir.y
			* (raycast->sidedist_x - raycast->deltadist_x);
		cube->textures.x = raycast->float_y - floor(raycast->float_y);
	}
	else
	{
		raycast->float_x = cube->player.pos_x + raycast->dir.x
			* (raycast->sidedist_y - raycast->deltadist_y);
		raycast->float_y = cube->player.pos_y + raycast->dir.y
			* (raycast->sidedist_y - raycast->deltadist_y);
		cube->textures.x = raycast->float_x - floor(raycast->float_x);
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
		if (cube->map.final_grid[raycast->int_y][raycast->int_x] == '1')
		{
			hit = false;
			return (if_wall_hit(cube, raycast, side));
		}
	}
	return (0);
}

static t_img	*assign_texture_and_render(t_textures *textures,
		t_raycast *raycast, int side)
{
	if (raycast->dir.x > 0 && side == 0)
	{
		textures->y = textures->ea_img.ht / raycast->wall_height;
		return (&textures->ea_img);
	}
	else if (raycast->dir.x < 0 && side == 0)
	{
		textures->y = textures->we_img.ht / raycast->wall_height;
		textures->x = 1 - textures->x;
		return (&textures->we_img);
	}
	else if (raycast->dir.y > 0 && side == 1)
	{
		textures->y = textures->no_img.ht / raycast->wall_height;
		textures->x = 1 - textures->x;
		return (&textures->no_img);
	}
	else if (raycast->dir.y < 0 && side == 1)
	{
		textures->y = textures->so_img.ht / raycast->wall_height;
		return (&textures->so_img);
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
