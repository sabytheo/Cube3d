/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:47:04 by egache            #+#    #+#             */
/*   Updated: 2025/11/26 15:04:20 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	init_minimap_values(t_minimap *mmv, t_game *cube)
{
	mmv->mm_width = WIDTH * 0.2;
	mmv->player_triangle_size = 0.03 * mmv->mm_width;
	mmv->vision_range = 3;
	mmv->tile_width = mmv->mm_width / (mmv->vision_range * 2);
	mmv->tile_height = mmv->tile_width;
	mmv->player_offset_x = (cube->player.pos_x - floor(cube->player.pos_x))
		* mmv->tile_width;
	mmv->player_offset_y = (cube->player.pos_y - floor(cube->player.pos_y))
		* mmv->tile_height;
	mmv->grid_y_start = (int)cube->player.pos_y - mmv->vision_range;
	mmv->grid_x_start = (int)cube->player.pos_x - mmv->vision_range;
	mmv->grid_y_end = mmv->grid_y_start + (mmv->vision_range * 2) + 1;
	mmv->grid_x_end = mmv->grid_x_start + (mmv->vision_range * 2) + 1;
	mmv->step_y = mmv->tile_width * 0.1;
	mmv->step_x = mmv->step_y;
}

static void	draw_one_tile(t_game *cube, t_minimap *mmv, char c)
{
	if (c == '1')
		draw_wall_tile(cube, mmv);
	if (c == 'C')
		draw_closed_door_tile(cube, mmv);
}

static char	minimap_item_check(t_game *cube, int grid_x, int grid_y)
{
	if (grid_y < 0 || grid_y >= cube->map.grid_height)
		return ('0');
	if (!cube->map.final_grid[grid_y])
		return ('0');
	if (grid_x < 0 || grid_x >= (int)ft_strlen(cube->map.final_grid[grid_y]))
		return ('0');
	if ((cube->map.final_grid[grid_y][grid_x] == '1'
		|| cube->map.final_grid[grid_y][grid_x] == 'C'))
		return (cube->map.final_grid[grid_y][grid_x]);
	return ('0');
}

static void	draw_minimap_tiles(t_game *cube, t_minimap *mmv)
{
	mmv->offset_y = 0;
	mmv->grid_y = mmv->grid_y_start;
	while (mmv->grid_y < mmv->grid_y_end)
	{
		mmv->grid_x = mmv->grid_x_start;
		mmv->offset_x = 0;
		while (mmv->grid_x < mmv->grid_x_end)
		{
			mmv->c = minimap_item_check(cube, mmv->grid_x, mmv->grid_y);
			if (mmv->c != '0')
				draw_one_tile(cube, mmv, mmv->c);
			mmv->grid_x++;
			mmv->offset_x += mmv->tile_width;
		}
		mmv->grid_y++;
		mmv->offset_y += mmv->tile_height;
	}
}

void	render_minimap(t_img *minimap_img, t_game *cube)
{
	t_minimap	mmv;

	mmv = cube->minimap_values;
	init_minimap_values(&mmv, cube);
	draw_minimap_background(&mmv, minimap_img);
	draw_minimap_tiles(cube, &mmv);
	draw_minimap_player(minimap_img, cube, &mmv);
	draw_minimap_borders(minimap_img, mmv.mm_width, mmv.tile_width);
}
