/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/23 19:37:14 by tsaby            ###   ########.fr       */
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

// void render_floor_ceilling(t_img *img, t_texture *textures)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	int c_color = get_color(textures->ceiling[0], textures->ceiling[1], textures->ceiling[2]);
// 	int f_color = get_color(textures->floor[0], textures->floor[1], textures->floor[2]);
// 	while (i < WIDTH)
// 	{
// 		j = 0;
// 		while (j < HEIGHT / 2)
// 		{
// 			img_pixel_put(img, i, j, c_color);
// 			j++;
// 		}
// 		j = HEIGHT / 2;
// 		while (j < HEIGHT)
// 		{
// 			img_pixel_put(img, i, j, f_color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return;
// }

void render_floor_ceilling(t_img *img, t_texture *textures, int x, int draw_start, int draw_end)
{
	int j;

	int c_color = get_color(textures->ceiling[0], textures->ceiling[1], textures->ceiling[2]);
	int f_color = get_color(textures->floor[0], textures->floor[1], textures->floor[2]);
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
	return;
}

unsigned int get_texture_pixel( float text_y,t_img *img,float text_x)
{
	return (*(unsigned int *)(img->addr + ((int)text_y * img->size_line + ((int)(text_x * 256)) * (img->bits_per_pixel / 8))));
}

void render_textured_floor_ceiling(t_game *cube, int x, float draw_start, float draw_end)
{
	int y;
	int p;
	float row_distance;
	float floor_x;
	float floor_y;
	float t_x;
	float t_y;
	float text_x;
	float text_y;

	y = 0;
	while(y < draw_start)
	{
		p = HEIGHT / 2 - y ;
		row_distance = ((cube->raycast->d_plan * 0.5) / p) ;
		floor_x = cube->player->pos_x + cube->raycast->dir->x * row_distance;
		floor_y = cube->player->pos_y + cube->raycast->dir->y * row_distance;
		t_x = floor_x - floor(floor_x);
		t_y = floor_y - floor(floor_y);
		text_x = t_x;
		text_y = t_y  * 256;
		img_pixel_put(cube->img, x, y, get_texture_pixel(text_y,&cube->textures.DO_img,text_x));
		y++;
	}
	y = draw_end + 1;
	while (y < HEIGHT)
	{
		p = y - HEIGHT / 2 ;
		row_distance = (cube->raycast->d_plan * 0.5) / p ;
		floor_x = cube->player->pos_x + cube->raycast->dir->x * row_distance;
		floor_y = cube->player->pos_y + cube->raycast->dir->y * row_distance;
		t_x = floor_x - floor(floor_x);
		t_y = floor_y - floor(floor_y);
		text_x = t_x;
		text_y = t_y  * 256;
		img_pixel_put(cube->img, x, y, get_texture_pixel(text_y,&cube->textures.DO_img,text_x));
		y++;
	}

}


void render_wall(float wall_height, t_game *cube, int x, t_img *img)
{
	int start_y;
	int j;
	int draw_start;
	int draw_end;
	float text_y;
	cube->textures.y = (float)256 / cube->raycast->wall_height;
	if (cube->textures.y <= 0)
		cube->textures.y = 0.01;
	// printf("cube->textures.y : %.2f\n", cube->textures.y);
	text_y = 0;
	// printf(" x = %d wall height = %f\n", x, wall_height);
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
		render_textured_floor_ceiling(cube, x, draw_start, draw_end);
	j = draw_start;
	while (j < draw_end)
	{
		img_pixel_put(cube->img, x, j, get_texture_pixel(text_y,img,cube->textures.x));
		text_y += cube->textures.y;
		j++;
	}
}

void init_raycast_values(t_game *cube, t_raycast *raycast, int x)
{
	float camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	raycast->angle = cube->player->angle + atan(camera_x * cube->player->tan_fov_2);
	raycast->dir->x = cos(raycast->angle);
	raycast->dir->y = -sin(raycast->angle);
	raycast->deltaDistX = fabs(1 / raycast->dir->x);
	raycast->deltaDistY = fabs(1 / raycast->dir->y);
	raycast->intX = (int)cube->player->pos_x;
	raycast->intY = (int)cube->player->pos_y;
	raycast->floatX = cube->player->pos_x;
	raycast->floatY = cube->player->pos_y;
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
	if (cube->raycast->corrected_distance <= 0)
		cube->raycast->corrected_distance = 0.1;
	cube->raycast->wall_height = (cube->raycast->base_height * cube->raycast->d_plan) / cube->raycast->corrected_distance;
}



void init_raycast_direction(t_game *cube, t_raycast *raycast)
{
	if (raycast->dir->x < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (cube->player->pos_x - raycast->intX) * raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->intX + 1.0 - cube->player->pos_x) * raycast->deltaDistX;
	}
	if (raycast->dir->y < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (cube->player->pos_y - raycast->intY) * raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->intY + 1.0 - cube->player->pos_y) * raycast->deltaDistY;
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
				raycast->floatX = cube->player->pos_x + raycast->dir->x * (raycast->sideDistX - raycast->deltaDistX);
				raycast->floatY = cube->player->pos_y + raycast->dir->y * (raycast->sideDistX - raycast->deltaDistX);
				cube->textures.x = raycast->floatY - floor(raycast->floatY);
			}
			else
			{
				raycast->floatX = cube->player->pos_x + raycast->dir->x * (raycast->sideDistY - raycast->deltaDistY);
				raycast->floatY = cube->player->pos_y + raycast->dir->y * (raycast->sideDistY - raycast->deltaDistY);
				cube->textures.x = raycast->floatX - floor(raycast->floatX);
			}
			hit = true;
			return (side);
		}
		if (cube->map->final_grid[raycast->intY][raycast->intX] == 'C')
		{
			if (!side)
			{
				raycast->floatX = cube->player->pos_x + raycast->dir->x * (raycast->sideDistX - raycast->deltaDistX);
				raycast->floatY = cube->player->pos_y + raycast->dir->y * (raycast->sideDistX - raycast->deltaDistX);
				cube->textures.x = raycast->floatY - floor(raycast->floatY);
			}
			else
			{
				raycast->floatX = cube->player->pos_x + raycast->dir->x * (raycast->sideDistY - raycast->deltaDistY);
				raycast->floatY = cube->player->pos_y + raycast->dir->y * (raycast->sideDistY - raycast->deltaDistY);
				cube->textures.x = raycast->floatX - floor(raycast->floatX);
			}
			hit = true;
			cube->map->door_found = true;
			return (side);
		}
	}
	return (0);
}

/*

trouver le ratio (si on avance )
taille en rapport avec la distance

*/
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
		if (cube->map->door_found)
		{
			cube->textures.y = cube->textures.DO_img.height / cube->raycast->wall_height;
			render_wall(raycast->wall_height, cube, x, &cube->textures.DO_img);
		}
		else
		{
			if (raycast->dir->x > 0 && side == 0)
			{
				cube->textures.y = cube->textures.EA_img.height / cube->raycast->wall_height;
				cube->textures.x = 1 - cube->textures.x;
				render_wall(raycast->wall_height, cube, x, &cube->textures.EA_img);
			}
			else if (raycast->dir->x < 0 && side == 0)
			{
				cube->textures.y = cube->textures.WE_img.height / cube->raycast->wall_height;
				render_wall(raycast->wall_height, cube, x, &cube->textures.WE_img);
			}
			else if (raycast->dir->y > 0 && side == 1)
			{
				cube->textures.y = cube->textures.NO_img.height / cube->raycast->wall_height;
				render_wall(raycast->wall_height, cube, x, &cube->textures.NO_img);
			}
			else if (raycast->dir->y < 0 && side == 1)
			{
				cube->textures.y = cube->textures.SO_img.height / cube->raycast->wall_height;
				cube->textures.x = 1 - cube->textures.x;
				render_wall(raycast->wall_height, cube, x, &cube->textures.SO_img);
			}
		}
		cube->map->door_found = false;
		x++;
	}
	return;
}

void render(t_game *cube)
{
	// render_floor_ceilling(cube->img, &cube->textures);
	update_fps_counter(cube);
	raycast(cube, cube->raycast);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img_ptr, 0, 0);
	draw_debug_info_cardinal(cube);
}
