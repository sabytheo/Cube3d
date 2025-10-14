/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/14 15:36:00 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int get_color(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void img_pixel_put(t_img *img, int x, int y, int color)
{
	char *pixel;
	int i;

	i = img->bits_per_pixel - 8;
	pixel = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	while (i > 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bits_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}
void render_floor_ceilling(t_img *img, t_texture *textures)
{
	int i;
	int j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			img_pixel_put(img, i, j, get_color(textures->ceiling[0], textures->ceiling[1], textures->ceiling[2]));
			j++;
		}
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			img_pixel_put(img, i, j, get_color(textures->floor[0], textures->floor[1], textures->floor[2]));
			j++;
		}
		i++;
	}
	return;
}

void render_wall(float wall_height, t_game *cube, int x, int color)
{
	int start_y;
	int j;
	int draw_start;
	int draw_end;

	// printf(" x = %d wall height = %f\n", x, wall_height);
	start_y = HEIGHT / 2;
	draw_start = (start_y - (wall_height * 0.5));
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (start_y + (wall_height * 0.5));
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	j = draw_start;
	while (j <= draw_end)
	{
		img_pixel_put(cube->img, x, j, color);
		j++;
	}
}

void	init_raycast_values(t_game *cube, t_raycast *raycast, int x)
{
	float camera_x;
	
	camera_x = 2 * x / (float)WIDTH - 1;
	raycast->angle = cube->player->angle + atan(camera_x * tan(cube->player->fov / 2));
	raycast->dir->x = cos(raycast->angle);
	raycast->dir->y = -sin(raycast->angle);
	raycast->deltaDistX = fabs(1 / raycast->dir->x);
	raycast->deltaDistY = fabs(1 / raycast->dir->y);
	raycast->mapX = (int)cube->player->pos_x;
	raycast->mapY = (int)cube->player->pos_y;
}

static void init_height_dplan(t_game *cube)
{
	cube->raycast->base_height = 1;
	cube->raycast->d_plan = WIDTH / (2 * tan(cube->player->fov * 0.5));
	return;
}

static void get_distance_and_wallheight(t_game *cube)
{
	cube->raycast->corrected_distance = cube->raycast->distance * cos(cube->raycast->angle - cube->player->angle);
	cube->raycast->wall_height = (cube->raycast->base_height * cube->raycast->d_plan) / cube->raycast->corrected_distance;
}

void	init_raycast_direction(t_game *cube, t_raycast *raycast)
{
	if (raycast->dir->x < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (cube->player->pos_x - raycast->mapX) * raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->mapX + 1.0 - cube->player->pos_x) * raycast->deltaDistX;
	}
	if (raycast->dir->y < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (cube->player->pos_y - raycast->mapY) * raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->mapY + 1.0 - cube->player->pos_y) * raycast->deltaDistY;
	}
}

int ray_displacement(t_game *cube, t_raycast *raycast)
{
	bool hit;
	int side;
	
	hit = false;
	while (hit == false)
	{
		if (raycast->sideDistX < raycast->sideDistY)
		{
			raycast->sideDistX += raycast->deltaDistX;
			raycast->mapX += raycast->stepX;
			side = 0;
		}
		else
		{
			raycast->sideDistY += raycast->deltaDistY;
			raycast->mapY += raycast->stepY;
			side = 1;
		}
		if (cube->map->final_grid[raycast->mapY][raycast->mapX] == '1')
		{
			hit = true;
			return (side);
			// printf("Rayon %d: mur trouvé à (%.2f, %.2f)\n", x, cube->player->pos_x, cube->player->pos_y);
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
			raycast->distance = (raycast->mapX - cube->player->pos_x + (1 - raycast->stepX) / 2) / raycast->dir->x;
		else
			raycast->distance = (raycast->mapY - cube->player->pos_y + (1 - raycast->stepY) / 2) / raycast->dir->y;
		get_distance_and_wallheight(cube);
				if (raycast->dir->x > 0 && side == 0)
			render_wall(raycast->wall_height, cube, x, BLUE);
		else if (raycast->dir->x < 0 && side == 0)
			render_wall(raycast->wall_height, cube, x, RED);
		else if (raycast->dir->y > 0 && side == 1)
			render_wall(raycast->wall_height, cube, x, GREEN);
		else if (raycast->dir->y < 0 && side == 1)
			render_wall(raycast->wall_height, cube, x, PURPLE);
		x++;
	}
	return;
}

void render(t_game *cube)
{
	render_floor_ceilling(cube->img, cube->textures);
	raycast(cube, cube->raycast);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img_ptr, 0, 0);

}
