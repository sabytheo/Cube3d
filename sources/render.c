/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/09 12:40:49 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	get_color(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

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
void	render_floor_ceilling(t_img *img, t_texture *textures)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			img_pixel_put(img, i, j, get_color(textures->ceiling[0],
					textures->ceiling[1], textures->ceiling[2]));
			j++;
		}
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			img_pixel_put(img, i, j, get_color(textures->floor[0],
					textures->floor[1], textures->floor[2]));
			j++;
		}
		i++;
	}
	return ;
}

void	render_wall(float wall_height, t_game *cube, int x)
{
	int	start_y;
	int	j;
	int	draw_start;
	int	draw_end;

	printf(" x = %d wall height = %f\n", x, wall_height);
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
		img_pixel_put(cube->img, x, j, WHITE);
		j++;
	}
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img_ptr, 0, 0);
}
// void	launch_rayon(t_game *cube)
// {
// 	t_vector	dir;
// 	int			x;
// 	float		R_H;
// 	float		angle;
// 	float		distance;
// 	float		no_fish_distance;
// 	float		wall_height;
// 	float		base_height;
// 	float		deltaDistY;
// 	float		deltaDistX;
// 	float		d_plan;
// 	float sideDistX;
// 	float sideDistY;
// 	int stepY;
// 	int stepX;
// 	int mapX;
// 	int mapY;
// 	bool hit;
// 	int side;

// 	base_height = 1;
// 	side = 0;
// 	R_H = 2 * tan(cube->player->fov * 0.5) / WIDTH;
// 	d_plan = WIDTH / (2 * tan(cube->player->fov * 0.5));
// 	x = 0;
// 	while (x <= WIDTH)
// 	{
// 		hit = false;
// 		angle = cube->player->angle - (x - WIDTH * 0.5) * R_H;
// 		dir.x = cos(angle);
// 		dir.y = -sin(angle);
// 		deltaDistX = fabs(1 / dir.x);
// 		deltaDistY = fabs(1 / dir.y);
// 		mapX = (int)cube->player->pos_x;
// 		mapY = (int)cube->player->pos_y;
// 		if (dir.x < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (cube->player->pos_x - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - cube->player->pos_x) * deltaDistX;
// 		}
// 		if (dir.y < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (cube->player->pos_y - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - cube->player->pos_y) * deltaDistY;
// 		}
// 		while (hit == false)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if (cube->map->final_grid[mapY][mapX] == '1')
// 			{
// 				hit = true;
// 				printf("Rayon %d: mur trouvé à (%.2f, %.2f)\n", x,
// cube->player->pos_x, cube->player->pos_y);
// 			}
// 		}
// 		if (side == 0)
//             distance = (mapX - cube->player->pos_x + (1 - stepX) / 2)
// / dir.x;
//         else
//             distance = (mapY - cube->player->pos_y + (1 - stepY) / 2)
// / dir.y;
// 		no_fish_distance = distance * cos(angle - cube->player->angle);
// 		wall_height = (base_height * d_plan) / no_fish_distance;
// 		render_wall(wall_height, cube, x);
// 		x++;
// 	}
// 	return ;
// }

static void	init_raycast(t_game *cube)
{
	cube->raycast->base_height = 1;
	cube->raycast->R_H = 2 * tan(cube->player->fov * 0.5) / WIDTH;
	cube->raycast->d_plan = WIDTH / (2 * tan(cube->player->fov * 0.5));
	return ;
}

static void	get_distance_and_wallheight(t_game *cube, t_vector rayon)
{
	cube->raycast->distance = sqrt(pow(rayon.x - cube->player->pos_x, 2)
			+ pow(rayon.y - cube->player->pos_y, 2));
	cube->raycast->corrected_distance = cube->raycast->distance
		* cos(cube->raycast->angle - cube->player->angle);
	cube->raycast->wall_height = (cube->raycast->base_height
			* cube->raycast->d_plan) / cube->raycast->corrected_distance;
}

void	raycast(t_game *cube, t_raycast *raycast)
{
	t_vector	ray;
	t_vector	dir;
	int			x;

	cube->raycast->dir = &dir;
	init_raycast(cube);
	x = 0;
	while (x <= WIDTH)
	{
		raycast->angle = cube->player->angle - (x - WIDTH * 0.5) * raycast->R_H;
		dir.x = cos(raycast->angle) * 0.001;
		dir.y = -sin(raycast->angle) * 0.001;
		ray.x = cube->player->pos_x;
		ray.y = cube->player->pos_y;
		while (cube->map->final_grid[(int)ray.y][(int)ray.x] != '1')
		{
			ray.x += dir.x;
			ray.y += dir.y;
		}
		get_distance_and_wallheight(cube, ray);
		render_wall(raycast->wall_height, cube, x);
		x++;
	}
	return ;
}

void	render(t_game *cube)
{
	render_floor_ceilling(cube->img, cube->textures);
	raycast(cube, cube->raycast);
}
