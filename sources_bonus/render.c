/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/07 17:03:56 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	render_ceil(t_cube_thread *cube_thread, float draw_start, int x,
		float correction)
{
	int		p;
	float	floor_x;
	float	floor_y;
	float	row_distance;
	int		y;

	y = 0;
	while (y < draw_start)
	{
		p = HEIGHT / 2 - y;
		row_distance = ((cube_thread->raycast.d_plan * 0.5) / p) / correction;
		floor_x = cube_thread->cube->player.pos_x + cube_thread->raycast.dir.x
			* row_distance;
		floor_y = cube_thread->cube->player.pos_y + cube_thread->raycast.dir.y
			* row_distance;
		img_pixel_put(cube_thread->cube->img, x, y, get_texture_pixel((floor_y
					- floor(floor_y)) * cube_thread->textures.CE_img.ht,
				&cube_thread->textures.CE_img, floor_x - floor(floor_x)));
		y++;
	}
}

static void	render_floor(t_cube_thread *cube_thread, float draw_end, int x,
		float correction)
{
	int		p;
	float	floor_x;
	float	floor_y;
	float	row_distance;
	int		y;

	y = draw_end + 1;
	while (y < HEIGHT)
	{
		p = y - HEIGHT / 2;
		row_distance = ((cube_thread->raycast.d_plan * 0.5) / p) / correction;
		floor_x = cube_thread->cube->player.pos_x + cube_thread->raycast.dir.x
			* row_distance;
		floor_y = cube_thread->cube->player.pos_y + cube_thread->raycast.dir.y
			* row_distance;
		img_pixel_put(cube_thread->cube->img, x, y, get_texture_pixel((floor_y
					- floor(floor_y)) * cube_thread->textures.FL_img.ht,
				&cube_thread->textures.FL_img, floor_x - floor(floor_x)));
		y++;
	}
}

void	render_textured_floor_ceiling(t_cube_thread *cube_thread, int x,
		float draw_start, float draw_end)
{
	float	correction;

	correction = cos(cube_thread->raycast.angle
			- cube_thread->cube->player.angle);
	if (correction < 0.01)
		correction = 0.01;
	render_ceil(cube_thread, draw_start, x, correction);
	render_floor(cube_thread, draw_end, x, correction);
}

void	render_wall_pixel(t_cube_thread *cube_thread, int x, int *j,
		float *text_y)
{
	int	color;

	color = get_texture_pixel(*text_y, cube_thread->raycast.texture_assigned,
			cube_thread->textures.x);
	if (color != 16777215)
		img_pixel_put(cube_thread->cube->img, x, *j, color);
	*text_y += cube_thread->textures.y;
	(*j)++;
}

void	render_wall(float wall_height, t_cube_thread *cube_thread, int x,
		t_raycast *raycast)
{
	int		j;
	int		draw_start;
	int		draw_end;
	float	text_y;

	cube_thread->textures.y = raycast->texture_assigned->ht
		/ raycast->wall_height;
	if (cube_thread->textures.y <= 0)
		cube_thread->textures.y = 0.01;
	text_y = 0;
	draw_start = (raycast->start_y - (wall_height * 0.5));
	if (draw_start < 0)
	{
		text_y = (0 - draw_start) * cube_thread->textures.y;
		draw_start = 0;
	}
	draw_end = (raycast->start_y + (wall_height * 0.5));
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	else
		render_textured_floor_ceiling(cube_thread, x, draw_start, draw_end);
	j = draw_start;
	while (j < draw_end)
		render_wall_pixel(cube_thread, x, &j, &text_y);
}

void launch_threads(t_game *cube)
{
	t_cube_thread	*cube_thread[cube->nb_cores];
	int				column_size;
	int				column_start;
	int				i;

	column_size = WIDTH / cube->nb_cores;
	column_start = 0;
	i = 0;
	while (i < cube->nb_cores)
	{
		cube_thread[i] = malloc(1 * sizeof(t_cube_thread));
		if (i == 0)
			cube_thread[i]->width_start = column_start;
		else
			cube_thread[i]->width_start = column_start + 1;
		cube_thread[i]->width_end = column_start + column_size;
		cube_thread[i]->cube = cube;
		cube_thread[i]->map = cube->map;
		cube_thread[i]->textures = cube->textures;
		cube_thread[i]->raycast = cube->raycast;
		cube_thread[i]->id = i;
		cube_thread[i]->map.final_grid = malloc(sizeof(char *)
				* cube->map.grid_height);
		for (int j = 0; j < cube->map.grid_height; j++)
			cube_thread[i]->map.final_grid[j] = ft_strdup(cube->map.final_grid[j]);
		// cube_thread[i]->img = cube->thread_img[i];
		if (pthread_create(&cube_thread[i]->thread, NULL, &raycast,
				cube_thread[i]))
		{
			return ;
		}
		column_start += column_size;
		i++;
	}
	i = 0;
	while (i < cube->nb_cores)
	{
		if (cube_thread[i])
			pthread_join(cube_thread[i]->thread, NULL);
		i++;
	}
}

void	render(t_game *cube)
{
	launch_threads(cube);
	render_mapmap(cube->minimap_img, cube);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->minimap_img->img, 0,
		0);
	update_fps_counter(cube);
	draw_debug_info_cardinal(cube);
}
