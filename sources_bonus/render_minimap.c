/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:47:04 by egache            #+#    #+#             */
/*   Updated: 2025/11/04 17:57:36 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	draw_minimap_background(t_img *minimap)
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
			img_pixel_put(minimap, i, j, get_color(0, 0, 0));
			i++;
		}
		j++;
	}
}

void	draw_minimap_player(t_img *minimap, t_game *cube)
{
	int	mm_width;
	int	width_center;
	int	height_center;
	int	offset_pos;
	int	offset_sin_cos;

	mm_width = WIDTH * 0.2;
	offset_pos = 1;
	width_center = mm_width * 0.5;
	height_center = width_center;
	while (offset_pos <= 10)
	{
		offset_sin_cos = 1;
		while (offset_sin_cos <= offset_pos)
		{
			img_pixel_put(minimap, (int)(width_center + offset_pos
					* cos(cube->player->angle + M_PI) + offset_sin_cos
					* cos(cube->player->angle + M_PI + M_PI_2)),
				(int)(height_center - offset_pos * sin(cube->player->angle
						+ M_PI) - offset_sin_cos * sin(cube->player->angle
						+ M_PI + M_PI_2)), get_color(255, 255, 0));
			img_pixel_put(minimap, (int)(width_center + offset_pos
					* cos(cube->player->angle + M_PI) - offset_sin_cos
					* cos(cube->player->angle + M_PI + M_PI_2)),
				(int)(height_center - offset_pos * sin(cube->player->angle
						+ M_PI) + offset_sin_cos * sin(cube->player->angle
						+ M_PI + M_PI_2)), get_color(0, 255, 255));
			offset_sin_cos++;
		}
		offset_pos++;
	}
}

void	draw_minimap_borders(t_img *minimap, int mm_width, int tile_width)
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
				img_pixel_put(minimap, i, j, get_color(255, 255, 255));
			i++;
		}
		j++;
	}
}

void	render_mapmap(t_img *minimap, t_game *cube)
{
	int		mm_width;
	int		vision_range;
	int		tile_width;
	int		tile_height;
	int		x;
	int		y;
	float	player_offset_x;
	float	player_offset_y;
	int		offset_y;
	int		offset_x;
	int		step_x;
	int		step_y;
	int		check_x;
	int		check_y;
	int		start_y;
	int		start_x;
	int		final_x;
	int		final_y;

	mm_width = (WIDTH * 0.2);
	vision_range = 3;
	tile_width = mm_width / (vision_range * 2);
	tile_height = tile_width;
	// print background
	draw_minimap_background(minimap);
	// print background
	// print walls
	player_offset_x = (cube->player->pos_x - floor(cube->player->pos_x))
		* tile_width;
	player_offset_y = (cube->player->pos_y - floor(cube->player->pos_y))
		* tile_height;
	offset_y = 0;
	check_x = 0;
	check_y = 0;
	start_y = (int)cube->player->pos_y - vision_range;
	start_x = (int)cube->player->pos_x - vision_range;
	y = start_y;
	while (y < start_y + (vision_range * 2) + 1)
	{
		x = start_x;
		offset_x = 0;
		while (x < start_x + (vision_range * 2) + 1)
		{
			if (y < 0)
				check_y = 0;
			if (x < 0)
				check_x = 0;
			if (cube->map->final_grid[check_y]
				&& cube->map->final_grid[check_y][check_x] && y >= 0
				&& y <= cube->map->grid_height && x >= 0
				&& x <= cube->map->max_width
				&& cube->map->final_grid[y][x] == '1')
			{
				step_x = tile_width * 0.1;
				while (step_x < tile_width)
				{
					step_y = tile_width * 0.1;
					while (step_y < tile_height)
					{
						final_x = offset_x + step_x - (int)player_offset_x;
						final_y = offset_y + step_y - (int)player_offset_y;
						if (final_x > tile_width * 0.1 && final_x < mm_width
							&& final_y > tile_width * 0.1 && final_y < mm_width)
							img_pixel_put(minimap, final_x, final_y,
								get_color(255, 255, 255));
						step_y++;
					}
					step_x++;
				}
				offset_x += tile_width;
			}
			else
				offset_x += tile_width;
			x++;
			check_x = x;
		}
		y++;
		check_y = y;
		offset_y += tile_height;
	}
	draw_minimap_player(minimap, cube);
	draw_minimap_borders(minimap, mm_width, tile_width);
}
