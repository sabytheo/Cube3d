/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:23:49 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:54:03 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	get_texture_coord_and_distance(t_game *cube, t_raycast *raycast,
		t_hit_info **new_hit, int side)
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
	if (side == 0)
		(*new_hit)->distance = (raycast->intX - cube->player.pos_x + (1
					- raycast->stepX) / 2) / raycast->dir.x;
	else
		(*new_hit)->distance = (raycast->intY - cube->player.pos_y + (1
					- raycast->stepY) / 2) / raycast->dir.y;
	(*new_hit)->side = side;
	(*new_hit)->texture_x = cube->textures.x;
	return ;
}
static void	collect_hits(t_game *cube, t_raycast *raycast, t_hit_info **hits,
		int *hit_count)
{
	int			side;
	bool		hit_wall;
	t_hit_info	*new_hit;

	hit_wall = false;
	while (!hit_wall)
	{
		side = init_hit_char(cube, raycast, &new_hit);
		if (side == -1)
			return (free(new_hit)) ;
		if (new_hit->hit_type == '1' || new_hit->hit_type == 'C'
			|| new_hit->hit_type == 'O')
		{
			get_texture_coord_and_distance(cube, raycast, &new_hit, side);
			*hits = realloc(*hits, sizeof(t_hit_info) * (*hit_count + 1));
			(*hits)[*hit_count] = *new_hit;
			(*hit_count)++;
			if (new_hit->hit_type == '1' || new_hit->hit_type == 'C')
			{
				free(new_hit);
				hit_wall = true;
			}
		}
	}
}
static t_img *assign_texture_and_current_hit(t_game *cube,t_raycast *raycast, t_hit_info *hits, int i)
{
	t_img		*texture;
	t_hit_info *current_hit;

	texture = NULL;
	current_hit = &hits[i];
	if (current_hit->hit_type == 'O')
		texture = &cube->textures.DO_img;
	else if (current_hit->hit_type == 'C')
		texture = &cube->textures.SP_img;
	else
	{
		if (raycast->dir.x > 0 && current_hit->side == 0)
			texture = &cube->textures.EA_img;
		else if (raycast->dir.x < 0 && current_hit->side == 0)
			texture = &cube->textures.WE_img;
		else if (raycast->dir.y > 0 && current_hit->side == 1)
			texture = &cube->textures.NO_img;
		else if (raycast->dir.y < 0 && current_hit->side == 1)
			texture = &cube->textures.SO_img;
	}
	raycast->distance = current_hit->distance;
	cube->textures.x = current_hit->texture_x;
	return (texture);
}

static void render_from_last_wall(t_game* cube,t_raycast *raycast,int x)
{
	t_img		*texture;
	int			hit_count;
	t_hit_info	*hits;
	int i;

	texture = NULL;
	hit_count = 0;
	hits = NULL;
	collect_hits(cube, raycast, &hits, &hit_count);
	i = hit_count - 1;
	while (i >= 0)
	{
		texture = assign_texture_and_current_hit(cube, raycast,hits, i);
		get_distance_and_wallheight(cube);
		if (texture)
		{
			cube->textures.y = texture->ht / cube->raycast.wall_height;
			raycast->texture_assigned = texture;
			render_wall(raycast->wall_height, cube, x);
		}
		i--;
	}
	if (hits)
		free(hits);
}

void	raycast(t_game *cube, t_raycast *raycast)
{
	int			x;

	init_height_dplan(cube);
	x = 0;
	while (x <= WIDTH)
	{
		init_raycast_values(cube, raycast, x);
		init_raycast_direction(cube, raycast);
		render_from_last_wall(cube,raycast,x);
		x++;
	}
}
