/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_elements.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:45:08 by egache            #+#    #+#             */
/*   Updated: 2025/11/05 14:49:23 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_bonus.h>

void	draw_minimap_background(t_img *minimap_img)
{
	int	i;
	int	j;
	int	mm_width;

	mm_width = WIDTH * 0.2;
	j = 0;
	while (j < mm_width)
	{
		i = 0;
		while (i < mm_width)
		{
			img_pixel_put(minimap_img, i, j, get_color(0, 0, 0));
			i++;
		}
		j++;
	}
}

static void	calculate_triangle_offset(t_game *cube, t_minimap *mmv,
		int base_size, int width_offset)
{
	int	center;

	center = mmv->mm_width * 0.5;
	mmv->center_line_x = center + base_size * cos(cube->player->angle + M_PI);
	mmv->width_offset_x = width_offset * cos(cube->player->angle + M_PI
			+ M_PI_2);
	mmv->center_line_y = center - base_size * sin(cube->player->angle + M_PI);
	mmv->width_offset_y = width_offset * sin(cube->player->angle + M_PI
			+ M_PI_2);
}

void	draw_minimap_player(t_img *minimap_img, t_game *cube, t_minimap *mmv)
{
	int	triangle_base_size;
	int	width_offset_pixel;

	triangle_base_size = 1;
	while (triangle_base_size <= 10)
	{
		width_offset_pixel = 1;
		while (width_offset_pixel <= triangle_base_size)
		{
			calculate_triangle_offset(cube, mmv, triangle_base_size,
				width_offset_pixel);
			img_pixel_put(minimap_img, (int)(mmv->center_line_x
					+ mmv->width_offset_x), (int)(mmv->center_line_y
					- mmv->width_offset_y), get_color(255, 255, 0));
			img_pixel_put(minimap_img, (int)(mmv->center_line_x
					- mmv->width_offset_x), (int)(mmv->center_line_y
					+ mmv->width_offset_y), get_color(0, 255, 255));
			width_offset_pixel++;
		}
		triangle_base_size++;
	}
}

void	draw_minimap_borders(t_img *minimap_img, int mm_width, int tile_width)
{
	int	j;
	int	i;

	j = 0;
	while (j <= mm_width)
	{
		i = 0;
		while (i <= mm_width)
		{
			if (i > mm_width - (tile_width * 0.2) || i < (tile_width * 0.2)
				|| j < (tile_width * 0.2) || j > mm_width - (tile_width * 0.2))
			{
				img_pixel_put(minimap_img, i, j, get_color(255, 141, 161));
			}
			i++;
		}
		j++;
	}
	// j = (tile_width * 0.2) * 0.2;
	// while (j < ((tile_width * 0.2) - ((tile_width * 0.2) * 0.2)))
	// {
	// 	i = (tile_width * 0.2) * 0.2;
	// 	while (i < mm_width - (tile_width * 0.2) * 0.2)
	// 	{
	// 		img_pixel_put(minimap_img, i, j, get_color(255, 0, 255));
	// 		i++;
	// 	}
	// 	j++;
	// }
}

void	draw_wall_tile(t_game *cube, t_minimap *mmv)
{
	mmv->step_x = mmv->tile_width * 0.1;
	while (mmv->step_x < mmv->tile_width)
	{
		mmv->step_y = mmv->tile_width * 0.1;
		while (mmv->step_y < mmv->tile_height)
		{
			mmv->pixel_x = mmv->offset_x + mmv->step_x
				- (int)mmv->player_offset_x;
			mmv->pixel_y = mmv->offset_y + mmv->step_y
				- (int)mmv->player_offset_y;
			if (mmv->pixel_x > mmv->tile_width * 0.1
				&& mmv->pixel_x < mmv->mm_width
				&& mmv->pixel_y > mmv->tile_width * 0.1
				&& mmv->pixel_y < mmv->mm_width)
				img_pixel_put(cube->minimap_img, mmv->pixel_x, mmv->pixel_y,
					get_color(255, 255, 255));
			mmv->step_y++;
		}
		mmv->step_x++;
	}
}
