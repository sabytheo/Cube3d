/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/31 13:14:04 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"


void	render_textured_floor_ceiling(t_game *cube, int x, float draw_start,
		float draw_end)
{
	int		y;
	int		p;
	float	row_distance;
	float	floor_x;
	float	floor_y;
	float	t_x;
	float	t_y;
	float	text_x;
	float	text_y;
	float	correction;

	y = 0;
	correction = cos(cube->raycast->angle - cube->player->angle);
	if (correction < 0.01)
		correction = 0.01;
	while (y < draw_start)
	{
		p = HEIGHT / 2 - y;
		row_distance = ((cube->raycast->d_plan * 0.5) / p) / correction;
		floor_x = cube->player->pos_x + cube->raycast->dir->x * row_distance;
		floor_y = cube->player->pos_y + cube->raycast->dir->y * row_distance;
		t_x = floor_x - floor(floor_x);
		t_y = floor_y - floor(floor_y);
		text_x = t_x;
		text_y = t_y * 256;
		img_pixel_put(cube->img, x, y, get_texture_pixel(text_y,
				&cube->textures.CE_img, text_x));
		y++;
	}
	y = draw_end + 1;
	while (y < HEIGHT)
	{
		p = y - HEIGHT / 2;
		row_distance = ((cube->raycast->d_plan * 0.5) / p) / correction;
		floor_x = cube->player->pos_x + cube->raycast->dir->x * row_distance;
		floor_y = cube->player->pos_y + cube->raycast->dir->y * row_distance;
		t_x = floor_x - floor(floor_x);
		t_y = floor_y - floor(floor_y);
		text_x = t_x;
		text_y = t_y * 256;
		img_pixel_put(cube->img, x, y, get_texture_pixel(text_y,
				&cube->textures.FL_img, text_x));
		y++;
	}
}

void	render_wall(float wall_height, t_game *cube, int x, t_img *img)
{
	int				start_y;
	int				j;
	int				draw_start;
	int				draw_end;
	float			text_y;
	unsigned int	color;

	cube->textures.y = (float)img->ht / cube->raycast->wall_height;
	if (cube->textures.y <= 0)
		cube->textures.y = 0.01;
	text_y = 0;
	start_y = HEIGHT / 2;
	draw_start = (start_y - (wall_height * 0.5));
	if (draw_start < 0)
	{
		text_y = (0 - draw_start) * cube->textures.y;
		draw_start = 0;
	}
	draw_end = (start_y + (wall_height * 0.5));
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	else
	{
		render_textured_floor_ceiling(cube, x, draw_start, draw_end);
	}
	j = draw_start;
	while (j < draw_end)
	{
		color = get_texture_pixel(text_y, img, cube->textures.x);
		if (color != 16777215)
		{
			img_pixel_put(cube->img, x, j, color);
		}
		text_y += cube->textures.y;
		j++;
	}
}

void	render(t_game *cube)
{
	update_fps_counter(cube);
	raycast(cube, cube->raycast);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img, 0, 0);
	draw_debug_info_cardinal(cube);
}
