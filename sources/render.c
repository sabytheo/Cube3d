/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/21 14:43:00 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	render_floor_ceilling(t_game *cube, int x, int draw_start,
		int draw_end)
{
	int	j;
	int	c_color;
	int	f_color;

	c_color = get_color(cube->textures.ceiling[0], cube->textures.ceiling[1],
			cube->textures.ceiling[2]);
	f_color = get_color(cube->textures.floor[0], cube->textures.floor[1],
			cube->textures.floor[2]);
	j = 0;
	while (j < draw_start)
	{
		img_pixel_put(cube->img, x, j, c_color);
		j++;
	}
	j = draw_end + 1;
	while (j < HEIGHT)
	{
		img_pixel_put(cube->img, x, j, f_color);
		j++;
	}
	return ;
}

static void	init_textures_y(t_game *cube, t_img *texture)
{
	cube->textures.y = (float)texture->ht / cube->raycast.wall_height;
	if (cube->textures.y <= 0)
		cube->textures.y = 0.01;
}

void	render_wall(float wall_height, t_game *cube, int x, t_img *texture)
{
	int		draw_start;
	int		draw_end;
	float	text_y;

	init_textures_y(cube, texture);
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
		render_floor_ceilling(cube, x, draw_start, draw_end);
	while (draw_start < draw_end)
	{
		img_pixel_put(cube->img, x, draw_start, get_texture_pixel(text_y,
				texture, cube->textures.x));
		text_y += cube->textures.y;
		draw_start++;
	}
}
