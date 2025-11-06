/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_closed_door.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:42:14 by egache            #+#    #+#             */
/*   Updated: 2025/11/06 15:23:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_bonus.h>

static void	draw_top_closed_door_tile(t_game *cube, t_minimap *mmv)
{
	mmv->step_y = mmv->tile_width * 0.1;
	while (mmv->step_y < mmv->tile_height * 0.5)
	{
		mmv->pixel_x = mmv->offset_x + mmv->step_x - (int)mmv->player_offset_x;
		mmv->pixel_y = mmv->offset_y + mmv->step_y - (int)mmv->player_offset_y;
		if (mmv->pixel_x > mmv->tile_width * 0.1 && mmv->pixel_x < mmv->mm_width
			&& mmv->pixel_y > mmv->tile_width * 0.1
			&& mmv->pixel_y < mmv->mm_width)
			img_pixel_put(cube->minimap_img, mmv->pixel_x, mmv->pixel_y,
				get_color(255, 255, 255));
		mmv->step_y++;
	}
}

static void	draw_bottom_closed_door_tile(t_game *cube, t_minimap *mmv)
{
	mmv->step_y = mmv->tile_width * 0.1 + mmv->tile_height * 0.5;
	while (mmv->step_y < mmv->tile_height)
	{
		mmv->pixel_x = mmv->offset_x + mmv->step_x - (int)mmv->player_offset_x;
		mmv->pixel_y = mmv->offset_y + mmv->step_y - (int)mmv->player_offset_y;
		if (mmv->pixel_x > mmv->tile_width * 0.1 && mmv->pixel_x < mmv->mm_width
			&& mmv->pixel_y > mmv->tile_width * 0.1
			&& mmv->pixel_y < mmv->mm_width)
			img_pixel_put(cube->minimap_img, mmv->pixel_x, mmv->pixel_y,
				get_color(255, 255, 255));
		mmv->step_y++;
	}
}

static void	draw_left_closed_door_tile(t_game *cube, t_minimap *mmv)
{
	mmv->step_x = mmv->tile_width * 0.1;
	while (mmv->step_x < mmv->tile_width * 0.5)
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

static void	draw_right_closed_door_tile(t_game *cube, t_minimap *mmv)
{
	mmv->step_x = mmv->tile_width * 0.1 + mmv->tile_height * 0.5;
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

void	draw_closed_door_tile(t_game *cube, t_minimap *mmv)
{
	if (cube->map.final_grid[mmv->grid_y][mmv->grid_x + 1] == '1'
		&& cube->map.final_grid[mmv->grid_y][mmv->grid_x - 1] == '1')
	{
		mmv->step_x = mmv->tile_width * 0.1;
		while (mmv->step_x < mmv->tile_width)
		{
			draw_top_closed_door_tile(cube, mmv);
			draw_bottom_closed_door_tile(cube, mmv);
			mmv->step_x++;
		}
	}
	else if (cube->map.final_grid[mmv->grid_y + 1][mmv->grid_x] == '1'
		&& cube->map.final_grid[mmv->grid_y - 1][mmv->grid_x] == '1')
	{
		draw_left_closed_door_tile(cube, mmv);
		draw_right_closed_door_tile(cube, mmv);
	}
}
