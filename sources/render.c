/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/04 15:25:58 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	render_floor_ceilling(t_img *img, t_texture *textures, int x,
		int draw_start, int draw_end)
{
	int	j;
	int	c_color;
	int	f_color;

	c_color = get_color(textures->ceiling[0], textures->ceiling[1],
			textures->ceiling[2]);
	f_color = get_color(textures->floor[0], textures->floor[1],
			textures->floor[2]);
	j = 0;
	while (j < draw_start)
	{
		img_pixel_put(img, x, j, c_color);
		j++;
	}
	j = draw_end + 1;
	while (j < HEIGHT)
	{
		img_pixel_put(img, x, j, f_color);
		j++;
	}
	return ;
}

void	render_wall(float wall_height, t_game *cube, int x, t_img *img)
{
	int		start_y;
	int		j;
	int		draw_start;
	int		draw_end;
	float	text_y;

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
		render_floor_ceilling(cube->img, &cube->textures, x, draw_start,
			draw_end);
	j = draw_start;
	while (j < draw_end)
	{
		img_pixel_put(cube->img, x, j, get_texture_pixel(text_y, img,
				cube->textures.x));
		text_y += cube->textures.y;
		j++;
	}
}

void	render(t_game *cube)
{
	// render_floor_ceilling(cube->img, &cube->textures);
	update_fps_counter(cube);
	raycast(cube, cube->raycast);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img, 0, 0);
	draw_debug_info_cardinal(cube);
}
