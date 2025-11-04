/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:47:04 by egache            #+#    #+#             */
/*   Updated: 2025/11/04 23:35:43 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

void	draw_minimap_player(t_img *minimap_img, t_game *cube)
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
			img_pixel_put(minimap_img, (int)(width_center + offset_pos
					* cos(cube->player->angle + M_PI) + offset_sin_cos
					* cos(cube->player->angle + M_PI + M_PI_2)),
				(int)(height_center - offset_pos * sin(cube->player->angle
						+ M_PI) - offset_sin_cos * sin(cube->player->angle
						+ M_PI + M_PI_2)), get_color(255, 255, 0));
			img_pixel_put(minimap_img, (int)(width_center + offset_pos
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

void	init_minimap_values(t_minimap *mmv, t_game *cube)
{
	mmv->mm_width = WIDTH * 0.2;
	mmv->vision_range = 3;
	mmv->tile_width = mmv->mm_width / (mmv->vision_range * 2);
	mmv->tile_height = mmv->tile_width;
	mmv->player_offset_x = (cube->player->pos_x - floor(cube->player->pos_x))
		* mmv->tile_width;
	mmv->player_offset_y = (cube->player->pos_y - floor(cube->player->pos_y))
		* mmv->tile_height;
	mmv->grid_y_start = (int)cube->player->pos_y - mmv->vision_range;
	mmv->grid_x_start = (int)cube->player->pos_x - mmv->vision_range;
	mmv->grid_y_end = mmv->grid_y_start + (mmv->vision_range * 2) + 1;
	mmv->grid_x_end = mmv->grid_x_start + (mmv->vision_range * 2) + 1;
	mmv->grid_y_check = mmv->grid_y_start;
	mmv->grid_x_check = mmv->grid_x_start;
	mmv->step_y = mmv->tile_width * 0.1;
	mmv->step_x = mmv->step_y;
}

static char	minimap_item_check(t_game *cube, t_minimap *mmv, int grid_x,
		int grid_y)
{
	if (cube->map->final_grid[mmv->grid_y_check]
		&& cube->map->final_grid[mmv->grid_y_check][mmv->grid_x_check]
		&& grid_y >= 0 && grid_y <= cube->map->grid_height && grid_x >= 0
		&& grid_x <= cube->map->max_width
		&& (cube->map->final_grid[grid_y][grid_x] == '1'
			|| cube->map->final_grid[grid_y][grid_x] == 'B'
			|| cube->map->final_grid[grid_y][grid_x] == 'M'
			|| cube->map->final_grid[grid_y][grid_x] == 'C'))
		return (cube->map->final_grid[grid_y][grid_x]);
	return ('0');
}

static void	draw_wall_tile(t_game *cube, t_minimap *mmv)
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

static void	draw_closed_door_tile(t_game *cube, t_minimap *mmv)
{
	if (cube->map->final_grid[mmv->grid_y][mmv->grid_x + 1] == '1'
		&& cube->map->final_grid[mmv->grid_y][mmv->grid_x - 1] == '1')
	{
		mmv->step_x = mmv->tile_width * 0.1;
		while (mmv->step_x < mmv->tile_width)
		{
			draw_top_closed_door_tile(cube, mmv);
			draw_bottom_closed_door_tile(cube, mmv);
			mmv->step_x++;
		}
	}
	else if (cube->map->final_grid[mmv->grid_y + 1][mmv->grid_x] == '1'
		&& cube->map->final_grid[mmv->grid_y - 1][mmv->grid_x] == '1')
	{
		draw_left_closed_door_tile(cube, mmv);
		draw_right_closed_door_tile(cube, mmv);
	}
}

static void	draw_one_tile(t_game *cube, t_minimap *mmv, char c)
{
	if (c == '1')
		draw_wall_tile(cube, mmv);
	if (c == 'C')
		draw_closed_door_tile(cube, mmv);
}

void	draw_minimap_tiles(t_game *cube, t_minimap *mmv)
{
	mmv->offset_y = 0;
	mmv->grid_y = mmv->grid_y_start;
	mmv->grid_y_check = mmv->grid_y_start;
	while (mmv->grid_y < mmv->grid_y_end)
	{
		mmv->grid_x = mmv->grid_x_start;
		mmv->grid_x_check = mmv->grid_x_start;
		mmv->offset_x = 0;
		while (mmv->grid_x < mmv->grid_x_end)
		{
			if (mmv->grid_y < 0)
				mmv->grid_y_check = 0;
			if (mmv->grid_x < 0)
				mmv->grid_x_check = 0;
			mmv->c = minimap_item_check(cube, mmv, mmv->grid_x, mmv->grid_y);
			if (mmv->c != '0')
				draw_one_tile(cube, mmv, mmv->c);
			mmv->grid_x++;
			mmv->grid_x_check = mmv->grid_x;
			mmv->offset_x += mmv->tile_width;
		}
		mmv->grid_y++;
		mmv->grid_y_check = mmv->grid_y;
		mmv->offset_y += mmv->tile_height;
	}
}

void	render_mapmap(t_img *minimap_img, t_game *cube)
{
	t_minimap	*mmv;

	mmv = cube->minimap_values;
	init_minimap_values(cube->minimap_values, cube);
	draw_minimap_background(minimap_img);
	draw_minimap_tiles(cube, mmv);
	draw_minimap_player(minimap_img, cube);
	draw_minimap_borders(minimap_img, mmv->mm_width, mmv->tile_width);
}

// void	render_minimap(t_img *img, t_game *cube)
// {
// 	int		x;
// 	int		y;
// 	int		offset_x;
// 	int		offset_y;
// 	int		step_x;
// 	int		step_y;
// 	int		mm_width;
// 	int		tile_width;
// 	int		tile_height;
// 	float	draw_x;
// 	float	draw_y;
// 	int		offset_pos;
// 	int		offset_sin_cos;

// 	x = 0;
// 	y = 0;
// 	offset_y = HEIGHT * 0.1;
// 	step_x = 0;
// 	step_y = 0;
// 	mm_width = WIDTH * 0.8;
// 	tile_width = mm_width / cube->map->max_width;
// 	tile_height = tile_width;
// 	// Trouver la position du joueur en comparant x et y au floor de x et y du joueur.
// 	// Si vrai put pixel au ratio de la partie fractionnaire de la positon du joueur (si 17.5
// 	//	-> 0.5 donc a la moitie de la size de la tile + )
// 	while (cube->map->final_grid[y])
// 	{
// 		x = 0;
// 		offset_x = WIDTH * 0.1;
// 		while (cube->map->final_grid[y][x])
// 		{
// 			if (y == (int)cube->player->pos_y && x == (int)cube->player->pos_x)
// 			{
// 				draw_x = tile_width * (int)cube->player->pos_x + (tile_width
// 						* (cube->player->pos_x - floor(cube->player->pos_x)));
// 				draw_y = tile_width * (int)cube->player->pos_y + (tile_width
// 						* (cube->player->pos_y - floor(cube->player->pos_y)));
// 				img_pixel_put(img, ceil(draw_x), ceil(draw_y), get_color(0, 0,
// 						255));
// 				offset_pos = 1;
// 				while (offset_pos <= 5)
// 				{
// 					offset_sin_cos = 1;
// 					while (offset_sin_cos <= offset_pos)
// 					{
// 						img_pixel_put(img, (int)(draw_x + offset_pos
// 								* cos(cube->player->angle + M_PI)
// 								+ offset_sin_cos * cos(cube->player->angle
// 									+ M_PI + M_PI_2)), (int)(draw_y - offset_pos
// 								* sin(cube->player->angle + M_PI)
// 								- offset_sin_cos * sin(cube->player->angle
// 									+ M_PI + M_PI_2)), get_color(255, 255, 0));
// 						img_pixel_put(img, (int)(draw_x + offset_pos
// 								* cos(cube->player->angle + M_PI)
// 								- offset_sin_cos * cos(cube->player->angle
// 									+ M_PI + M_PI_2)), (int)(draw_y - offset_pos
// 								* sin(cube->player->angle + M_PI)
// 								+ offset_sin_cos * sin(cube->player->angle
// 									+ M_PI + M_PI_2)), get_color(0, 255, 255));
// 						offset_sin_cos++;
// 					}
// 					offset_pos++;
// 				}
// 			}
// 			if (cube->map->final_grid[y][x] == '1')
// 			{
// 				step_x = tile_width * 0.15;
// 				while (step_x < tile_width)
// 				{
// 					step_y = tile_width * 0.15;
// 					while (step_y < tile_height)
// 					{
// 						img_pixel_put(img, offset_x + step_x, offset_y + step_y,
// 							get_color(255, 255, 255));
// 						step_y++;
// 					}
// 					step_x++;
// 				}
// 			}
// 			else if (cube->map->final_grid[y][x] == 'C')
// 			{
// 				if (cube->map->final_grid[y][x + 1] == '1'
// 				&& cube->map->final_grid[y][x - 1] == '1')
// 				{
// 					step_x = tile_width * 0.15;
// 					while (step_x < tile_width)
// 					{
// 						step_y = tile_width * 0.15;
// 						while (step_y < tile_height * 0.5)
// 						{
// 							img_pixel_put(img, offset_x + step_x, offset_y + step_y,
// 								get_color(255, 255, 255));
// 							step_y++;
// 						}
// 						step_y = tile_width * 0.15 + tile_height * 0.5;
// 						while (step_y < tile_height)
// 						{
// 							img_pixel_put(img, offset_x + step_x, offset_y + step_y,
// 								get_color(255, 255, 255));
// 							step_y++;
// 						}
// 						step_x++;
// 					}
// 				}
// 				else if (cube->map->final_grid[y + 1][x] == '1'
// 				&& cube->map->final_grid[y - 1][x] == '1')
// 				{
// 					step_x = tile_width * 0.15;
// 					while (step_x < tile_width * 0.5)
// 					{
// 						step_y = tile_width * 0.15;
// 						while (step_y < tile_height)
// 						{
// 							img_pixel_put(img, offset_x + step_x, offset_y + step_y,
// 								get_color(255, 255, 255));
// 							step_y++;
// 						}
// 						step_x++;
// 					}
// 					step_x = tile_width * 0.15 + tile_width * 0.5;
// 					while (step_x < tile_width)
// 					{
// 						step_y = tile_width * 0.15;
// 						while (step_y < tile_height)
// 						{
// 							img_pixel_put(img, offset_x + step_x, offset_y + step_y,
// 								get_color(255, 255, 255));
// 							step_y++;
// 						}
// 						step_x++;
// 					}
// 				}
// 			}
// 			offset_x += tile_width;
// 			x++;
// 		}
// 		y++;
// 		offset_y += tile_height;
// 	}
// }
