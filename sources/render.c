/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/08 14:25:13 by tsaby            ###   ########.fr       */
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
	while (i >= 0)
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
	float	start_y;
	int		j;

	printf(" x = %d wall height = %2.f\n",x,wall_height);
	start_y = HEIGHT / 2;
	j = 0;
	while (j <= wall_height)
	{
		mlx_pixel_put(cube->mlx, cube->windows, x, (start_y - (wall_height * 0.5)) + j, WHITE);
		j++;
	}
}

void	launch_rayon(t_game *cube)
{
	t_vector	rayon;
	t_vector	dir;
	int			x;
	float		R_H;
	float		angle;
	float		distance;
	float		no_fish_distance;
	float		wall_height;
	float		base_height;
	float		d_plan;

	base_height = 1;
	R_H = 2 * tan(cube->player->fov * 0.5) / WIDTH;
	d_plan = WIDTH / (2 * tan(cube->player->fov * 0.5));
	x = 0;
	while (x <= WIDTH)
	{
		angle = cube->player->angle - (x - WIDTH * 0.5) * R_H;
		dir.x = cos(angle);
		dir.y = -sin(angle);
		rayon.x = cube->player->pos_x;
		rayon.y = cube->player->pos_y;
		while (cube->map->final_grid[(int)rayon.y][(int)rayon.x] != '1')
		{
			rayon.x += dir.x;
			rayon.y += dir.y;
		}
		printf("Rayon %d: mur trouvé à (%.2f, %.2f)\n", x, rayon.x, rayon.y);
		distance = sqrt(pow(rayon.x - cube->player->pos_x, 2) + pow(rayon.y
					- cube->player->pos_y, 2));
		no_fish_distance = distance * cos(angle - cube->player->angle);
		wall_height = (base_height * d_plan) / no_fish_distance;
		render_wall(wall_height, cube, x);
		x++;
	}
	return ;
}

void	render(t_game *cube)
{
	render_floor_ceilling(cube->img, cube->textures);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img_ptr, 0, 0);
	launch_rayon(cube);
}
