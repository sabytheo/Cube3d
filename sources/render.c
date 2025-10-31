/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/31 17:04:23 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int get_color(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->sl + x * (img->bpp / 8));
	while (i > 0)
	{
		if (img->en != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}


void	render_mapmap(t_img *minimap, t_game *cube)
{
	
	int width_center = (WIDTH * 0.2) * 0.5;
	int height_center = (WIDTH * 0.2) * 0.5;
	int vision_range = 3;
	int mm_width = (WIDTH * 0.2);
	int tile_width = mm_width / (vision_range * 2);
	int tile_height = tile_width;
	float player_offset_x = (cube->player->pos_x - floor(cube->player->pos_x)) * tile_width;
	float player_offset_y = (cube->player->pos_y - floor(cube->player->pos_y)) * tile_height;
	int x;
	int y;
	int offset_y = 0;
	int offset_x;
	int step_x;
	int step_y;
	int start_y = (int)cube->player->pos_y - vision_range;
	int start_x = (int)cube->player->pos_x - vision_range;

		int i;
	int j;

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

	y = start_y;
	while (y < start_y + (vision_range * 2))
	{
		x = start_x;
		offset_x = 0;
		while (x < start_x + (vision_range * 2))
		{
			if (y >= 0 && y < cube->map->grid_height && x >= 0 && x < cube->map->max_width 
				&& cube->map->final_grid[y][x] == '1')
			{
				step_x = tile_width * 0.15;
				while (step_x < tile_width)
				{
					step_y = tile_width * 0.15;
					while (step_y < tile_height)
					{
						float final_x = offset_x + step_x - player_offset_x;
						float final_y = offset_y + step_y - player_offset_y;
						if (final_x > tile_width * 0.1 && final_x <= mm_width + 1 && final_y > tile_width * 0.1 && final_y <= mm_width + 1)
							img_pixel_put(minimap, final_x, final_y, get_color(255, 255, 255));
						step_y++;
					}
					step_x++;
				}
				offset_x += tile_width;
			}
			else
				offset_x += tile_width;
			x++;
		}
		y++;
		offset_y += tile_height;
	}
	int offset_pos = 1;
	while (offset_pos <= 10)
	{					
		int offset_sin_cos = 1;
		while (offset_sin_cos <= offset_pos)
		{
			img_pixel_put(minimap, (int)(width_center + offset_pos * cos(cube->player->angle + M_PI) + offset_sin_cos * cos(cube->player->angle + M_PI + M_PI_2)), (int)(height_center - offset_pos * sin(cube->player->angle + M_PI) - offset_sin_cos * sin(cube->player->angle + M_PI + M_PI_2)), get_color(255, 255, 0));
			img_pixel_put(minimap, (int)(width_center + offset_pos * cos(cube->player->angle + M_PI) - offset_sin_cos * cos(cube->player->angle + M_PI + M_PI_2)), (int)(height_center - offset_pos * sin(cube->player->angle + M_PI) + offset_sin_cos * sin(cube->player->angle + M_PI + M_PI_2)), get_color(0, 255, 255));
			offset_sin_cos++;
		}
		offset_pos++;
	}
	j = 0;
	while (j < mm_width)
	{
		i = 0;
		while (i < mm_width)
		{
			if (i > mm_width - (tile_width * 0.2) || i < (tile_width * 0.2) || j < (tile_width * 0.2) || j > mm_width - (tile_width * 0.2))
				img_pixel_put(minimap, i, j, get_color(255, 0, 255));
			i++;
		}
		j++;
	}
}

void	render_minimap(t_img *img, t_game *cube)
{
	int x;
	int y;
	int offset_x;
	int offset_y;
	int step_x;
	int step_y;
	int mm_width;
	int tile_width;
	int tile_height;

	x = 0;
	y = 0;
	offset_y = 0;
	step_x = 0;
	step_y = 0;
	mm_width = WIDTH * 0.6;
	tile_width = mm_width / cube->map->max_width;
	tile_height = tile_width;

	//Trouver la position du joueur en comparant x et y au floor de x et y du joueur. 
	//Si vrai put pixel au ratio de la partie fractionnaire de la positon du joueur (si 17.5 -> 0.5 donc a la moitie de la size de la tile + )  
	while (cube->map->final_grid[y])
	{
		x = 0;
		offset_x = 0;
		while (cube->map->final_grid[y][x])
		{
			if (y == (int)cube->player->pos_y && x == (int)cube->player->pos_x)
			{
				float draw_x = tile_width * (int)cube->player->pos_x + (tile_width * (cube->player->pos_x - floor(cube->player->pos_x)));
				float draw_y = tile_width * (int)cube->player->pos_y + (tile_width * (cube->player->pos_y - floor(cube->player->pos_y)));
				img_pixel_put(img, ceil(draw_x), ceil(draw_y), get_color(0, 0, 255));
			
				int offset_pos = 1;
				while (offset_pos <= 5)
				{					
					int offset_sin_cos = 1;
					while (offset_sin_cos <= offset_pos)
					{
						img_pixel_put(img, (int)(draw_x + offset_pos * cos(cube->player->angle + M_PI) + offset_sin_cos * cos(cube->player->angle + M_PI + M_PI_2)), (int)(draw_y - offset_pos * sin(cube->player->angle + M_PI) - offset_sin_cos * sin(cube->player->angle + M_PI + M_PI_2)), get_color(255, 255, 0));
						img_pixel_put(img, (int)(draw_x + offset_pos * cos(cube->player->angle + M_PI) - offset_sin_cos * cos(cube->player->angle + M_PI + M_PI_2)), (int)(draw_y - offset_pos * sin(cube->player->angle + M_PI) + offset_sin_cos * sin(cube->player->angle + M_PI + M_PI_2)), get_color(0, 255, 255));
						offset_sin_cos++;
					}
					offset_pos++;
				}
			}
			// if (cube->map->final_grid[y][x] == '1' && (abs((x - (int)cube->player->pos_x)) < 3  && abs((y - (int)cube->player->pos_y)) < 3))
			if (cube->map->final_grid[y][x] == '1')
			{
				step_x = 0;
				while (step_x < tile_width)
				{
					step_y = 0;
					while (step_y < tile_height)
					{
						img_pixel_put(img, offset_x + step_x, offset_y + step_y, get_color(255, 255, 255));
						step_y++;
					}
					step_x++;
				}
				offset_x += tile_width;
			}
			else
				offset_x += tile_width;
			x++;
		}
		y++;
		offset_y += tile_height;
	}
}

void render_floor_ceilling(t_img *img, t_texture *textures, int x, int draw_start, int draw_end)
{
	int j;

	int c_color = get_color(textures->ceiling[0], textures->ceiling[1],
			textures->ceiling[2]);
	int f_color = get_color(textures->floor[0], textures->floor[1],
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

unsigned int	get_texture_pixel(float text_y, t_img *img, float text_x)
{
	return (*(unsigned int *)(img->addr + ((int)text_y * img->sl + ((int)(text_x * img->ht)) * (img->bpp / 8))));
}
void	render_wall(float wall_height, t_game *cube, int x, t_img *img)
{
	int				start_y;
	int				j;
	int				draw_start;
	int				draw_end;
	float			text_y;

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
		render_floor_ceilling(cube->img, &cube->textures, x, draw_start,draw_end);
	j = draw_start;
	while (j < draw_end)
	{
		img_pixel_put(cube->img, x, j, get_texture_pixel(text_y, img, cube->textures.x));
		text_y += cube->textures.y;
		j++;
	}
}

void	init_raycast_values(t_game *cube, t_raycast *raycast, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	raycast->angle = cube->player->angle - atan(camera_x
			* cube->player->tan_fov_2);
	raycast->dir->x = cos(raycast->angle);
	raycast->dir->y = -sin(raycast->angle);
	raycast->deltaDistX = fabs(1 / raycast->dir->x);
	raycast->deltaDistY = fabs(1 / raycast->dir->y);
	raycast->intX = (int)cube->player->pos_x;
	raycast->intY = (int)cube->player->pos_y;
	raycast->floatX = cube->player->pos_x;
	raycast->floatY = cube->player->pos_y;
}

static void	init_height_dplan(t_game *cube)
{
	cube->raycast->base_height = 1;
	cube->raycast->d_plan = WIDTH / (2 * tan(cube->player->fov * 0.5));
	return ;
}

static void	get_distance_and_wallheight(t_game *cube)
{
	cube->raycast->corrected_distance = cube->raycast->distance
		* cos(cube->raycast->angle - cube->player->angle);
	if (cube->raycast->corrected_distance <= 0)
		cube->raycast->corrected_distance = 0.1;
	cube->raycast->wall_height = (cube->raycast->base_height
			* cube->raycast->d_plan) / cube->raycast->corrected_distance;
}

void	init_raycast_direction(t_game *cube, t_raycast *raycast)
{
	if (raycast->dir->x < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (cube->player->pos_x - raycast->intX)
			* raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->intX + 1.0 - cube->player->pos_x)
			* raycast->deltaDistX;
	}
	if (raycast->dir->y < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (cube->player->pos_y - raycast->intY)
			* raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->intY + 1.0 - cube->player->pos_y)
			* raycast->deltaDistY;
	}
}

int	ray_displacement(t_game *cube, t_raycast *raycast)
{
	bool	hit;
	int		side;

	hit = false;
	while (hit == false)
	{
		if (raycast->sideDistX < raycast->sideDistY)
		{
			raycast->sideDistX += raycast->deltaDistX;
			raycast->intX += raycast->stepX;
			side = 0;
		}
		else
		{
			raycast->sideDistY += raycast->deltaDistY;
			raycast->intY += raycast->stepY;
			side = 1;
		}
		if (cube->map->final_grid[raycast->intY][raycast->intX] == '1')
		{
			if (!side)
			{
				raycast->floatX = cube->player->pos_x + raycast->dir->x
					* (raycast->sideDistX - raycast->deltaDistX);
				raycast->floatY = cube->player->pos_y + raycast->dir->y
					* (raycast->sideDistX - raycast->deltaDistX);
				cube->textures.x = raycast->floatY - floor(raycast->floatY);
			}
			else
			{
				raycast->floatX = cube->player->pos_x + raycast->dir->x
					* (raycast->sideDistY - raycast->deltaDistY);
				raycast->floatY = cube->player->pos_y + raycast->dir->y
					* (raycast->sideDistY - raycast->deltaDistY);
				cube->textures.x = raycast->floatX - floor(raycast->floatX);
			}
			hit = true;
			return (side);
		}
	}
	return (0);
}

void raycast(t_game *cube, t_raycast *raycast)
{
	int x;
	int side;

	init_height_dplan(cube);
	side = 0;
	x = 0;
	while (x <= WIDTH)
	{
		init_raycast_values(cube, raycast, x);
		init_raycast_direction(cube, raycast);
		side = ray_displacement(cube, raycast);
		if (side == 0)
			raycast->distance = (raycast->intX - cube->player->pos_x + (1 - raycast->stepX) / 2) / raycast->dir->x;
		else
			raycast->distance = (raycast->intY - cube->player->pos_y + (1 - raycast->stepY) / 2) / raycast->dir->y;
		get_distance_and_wallheight(cube);
		if (raycast->dir->x > 0 && side == 0)
		{
			cube->textures.y = cube->textures.EA_img.ht / cube->raycast->wall_height;
			cube->textures.x = 1 - cube->textures.x;
			render_wall(raycast->wall_height, cube, x, &cube->textures.EA_img);
		}
		else if (raycast->dir->x < 0 && side == 0)
		{
			cube->textures.y = cube->textures.WE_img.ht / cube->raycast->wall_height;
			render_wall(raycast->wall_height, cube, x, &cube->textures.WE_img);
		}
		else if (raycast->dir->y > 0 && side == 1)
		{
			cube->textures.y = cube->textures.NO_img.ht / cube->raycast->wall_height;
			render_wall(raycast->wall_height, cube, x, &cube->textures.NO_img);
		}
		else if (raycast->dir->y < 0 && side == 1)
		{
			cube->textures.y = cube->textures.SO_img.ht / cube->raycast->wall_height;
			cube->textures.x = 1 - cube->textures.x;
			render_wall(raycast->wall_height, cube, x, &cube->textures.SO_img);
		}
		x++;
	}
	return;
}
void	render(t_game *cube)
{
	// render_floor_ceilling(cube->img, &cube->textures);
	// update_fps_counter(cube);
	raycast(cube, cube->raycast);
	// render_minimap(cube->img, cube);
	render_mapmap(cube->minimap, cube);
	// render_player_minimap(cube->img, cube);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->minimap->img, 0, 0);
	// draw_debug_info_cardinal(cube);
}
