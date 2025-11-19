/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:23:49 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/19 19:32:19 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	get_texture_coord_and_distance(t_cube_thread *cube_thread,
		t_raycast *raycast, t_hit_info **new_hit, int side)
{
	if (!side)
	{
		raycast->floatX = cube_thread->cube->player.pos_x + raycast->dir.x
			* (raycast->sideDistX - raycast->deltaDistX);
		raycast->floatY = cube_thread->cube->player.pos_y + raycast->dir.y
			* (raycast->sideDistX - raycast->deltaDistX);
		cube_thread->textures.x = raycast->floatY - floor(raycast->floatY);
		(*new_hit)->distance = (raycast->intX - cube_thread->cube->player.pos_x
				+ (1 - raycast->stepX) * 0.5) / raycast->dir.x;
	}
	else
	{
		raycast->floatX = cube_thread->cube->player.pos_x + raycast->dir.x
			* (raycast->sideDistY - raycast->deltaDistY);
		raycast->floatY = cube_thread->cube->player.pos_y + raycast->dir.y
			* (raycast->sideDistY - raycast->deltaDistY);
		cube_thread->textures.x = raycast->floatX - floor(raycast->floatX);
		(*new_hit)->distance = (raycast->intY - cube_thread->cube->player.pos_y
				+ (1 - raycast->stepY) * 0.5) / raycast->dir.y;
	}
	(*new_hit)->side = side;
	(*new_hit)->texture_x = cube_thread->textures.x;
	return ;
}

static void	collect_hits(t_cube_thread *cube_thread, t_raycast *raycast,
		t_hit_info **hits, int *hit_count)
{
	int			side;
	bool		hit_wall;
	t_hit_info	*new_hit;

	hit_wall = false;
	while (!hit_wall)
	{
		side = init_hit_char(&cube_thread->map, raycast, &new_hit);
		if (side == -1)
			return (free(new_hit));
		if (new_hit->hit_type == '1' || new_hit->hit_type == 'C'
			|| new_hit->hit_type == 'O')
		{
			get_texture_coord_and_distance(cube_thread, raycast, &new_hit,
				side);
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

void	assign_texture_and_current_hit(t_cube_thread *cube_thread,
		t_raycast *raycast, t_hit_info *hits, int i)
{
	t_hit_info	*current_hit;

	current_hit = &hits[i];
	if (current_hit->hit_type == 'O')
		raycast->texture_assigned = &cube_thread->textures.DO_img;
	else if (current_hit->hit_type == 'C')
		raycast->texture_assigned = &cube_thread->textures.SP_img;
	else
	{
		if (raycast->dir.x > 0 && current_hit->side == 0)
			raycast->texture_assigned = &cube_thread->textures.EA_img;
		else if (raycast->dir.x < 0 && current_hit->side == 0)
			raycast->texture_assigned = &cube_thread->textures.WE_img;
		else if (raycast->dir.y > 0 && current_hit->side == 1)
			raycast->texture_assigned = &cube_thread->textures.NO_img;
		else if (raycast->dir.y < 0 && current_hit->side == 1)
			raycast->texture_assigned = &cube_thread->textures.SO_img;
	}
	raycast->distance = current_hit->distance;
	cube_thread->textures.x = current_hit->texture_x;
}

static void	render_from_last_wall(t_cube_thread *cube_thread, t_game *cube,
		t_raycast *raycast, int x)
{
	int			hit_count;
	t_hit_info	*hits;
	int			i;

	hit_count = 0;
	hits = NULL;
	collect_hits(cube_thread, raycast, &hits, &hit_count);
	i = hit_count - 1;
	while (i >= 0)
	{
		assign_texture_and_current_hit(cube_thread, raycast, hits, i);
		get_distance_and_wallheight(cube, raycast);
		if (raycast->texture_assigned)
			render_wall(raycast->wall_height, cube_thread, x, raycast);
		i--;
	}
	if (hits)
		free(hits);
}

void	*raycast(void *arg)
{
	t_cube_thread	*cube_thread;

	cube_thread = (t_cube_thread *)arg;
	while (cube_thread->width_start <= cube_thread->width_end)
	{
		init_raycast_values(cube_thread->cube, &cube_thread->raycast,
			cube_thread->width_start);
		init_raycast_direction(cube_thread->cube, &cube_thread->raycast);
		render_from_last_wall(cube_thread, cube_thread->cube,
			&cube_thread->raycast, cube_thread->width_start);
		cube_thread->width_start++;
	}
	return (NULL);
}
