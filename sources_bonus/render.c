/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 21:05:59 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	render_ceil(t_game *cube, float draw_start, int x, float correction)
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
		row_distance = ((cube->raycast.d_plan * 0.5) / p) / correction;
		floor_x = cube->player.pos_x + cube->raycast.dir.x * row_distance;
		floor_y = cube->player.pos_y + cube->raycast.dir.y * row_distance;
		img_pixel_put(cube->img, x, y, get_texture_pixel((floor_y
					- floor(floor_y)) * cube->textures.CE_img.ht,
				&cube->textures.CE_img, floor_x - floor(floor_x)));
		y++;
	}
}

static void	render_floor(t_game *cube, float draw_end, int x, float correction)
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
		row_distance = ((cube->raycast.d_plan * 0.5) / p) / correction;
		floor_x = cube->player.pos_x + cube->raycast.dir.x * row_distance;
		floor_y = cube->player.pos_y + cube->raycast.dir.y * row_distance;
		img_pixel_put(cube->img, x, y, get_texture_pixel((floor_y
					- floor(floor_y)) * cube->textures.FL_img.ht,
				&cube->textures.FL_img, floor_x - floor(floor_x)));
		y++;
	}
}

void	render_textured_floor_ceiling(t_game *cube, int x, float draw_start,
		float draw_end)
{
	float	correction;

	correction = cos(cube->raycast.angle - cube->player.angle);
	if (correction < 0.01)
		correction = 0.01;
	render_ceil(cube, draw_start, x, correction);
	render_floor(cube, draw_end, x, correction);
}

void	render_wall_pixel(t_game *cube,int x, int *j, float *text_y, t_img *img)
{
	int color;

	color = get_texture_pixel(*text_y, img, cube->textures.x);
	if (color != 16777215)
		img_pixel_put(cube->img, x, *j, color);
	*text_y += cube->textures.y;
	(*j)++;
}

void	render_wall(float wall_height, t_game *cube, int x)
{
	int				j;
	int				draw_start;
	int				draw_end;
	float			text_y;

	cube->textures.y = cube->raycast.texture_assigned->ht / cube->raycast.wall_height;
	if (cube->textures.y <= 0)
		cube->textures.y = 0.01;
	text_y = 0;
	draw_start = (cube->raycast.start_y - (wall_height * 0.5));
	if (draw_start < 0)
	{
		text_y = (0 - draw_start) * cube->textures.y;
		draw_start = 0;
	}
	draw_end = (cube->raycast.start_y + (wall_height * 0.5));
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	else
		render_textured_floor_ceiling(cube, x, draw_start, draw_end);
	j = draw_start;
	while (j < draw_end)
		render_wall_pixel(cube,x,&j,&text_y,cube->raycast.texture_assigned);
}

void	render(t_game *cube)
{
	update_fps_counter(cube);
	raycast(cube, &cube->raycast);
	render_mapmap(cube->minimap_img, cube);
	// render_minimap(cube->img, cube);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->minimap_img->img, 0,
		0);
	draw_debug_info_cardinal(cube);
}
