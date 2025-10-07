/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/07 21:27:40 by tsaby            ###   ########.fr       */
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

// void	launch_rayon(t_game *cube)
// {
// 	t_vector	rayon;
// 	int			x;
// 	float R_H;
// /*
// vecteur direction / vecteur plan
// */
// 	R_H = 2 * tan(cube->player->fov * 0.5) / WIDTH;
// 	printf("%f\n",R_H);
// 	x = 0;
// 	rayon.x = cube->player->pos_x;
// 	rayon.y = cube->player->pos_y;
// 	printf("pos x : %d  pos y : %d\n", (int)rayon.x, (int)rayon.y);
// 	while (x <= WIDTH)
// 	{
// 		printf("pos x : %d  pos y : %d\n", (int)rayon.x, (int)rayon.y);
// 		// rayon.x -= (x - WIDTH * 0.5) * R_H;
// 		rayon.x--;
// 		printf("%f\n",rayon.x);
// 		if (cube->map->final_grid[(int)rayon.x][(int)rayon.y] == '1')
// 		{
// 			printf("wall trouve a %d %d\n", (int)rayon.x, (int)rayon.y);
// 			break ;
// 		}
// 		x++;
// 	}
// }

void	launch_rayon(t_game *cube)
{
	t_vector	rayon;
	t_vector	dir;
	int			x;
	float		R_H;
	float		angle;
	int step;

	R_H = 2 * tan(cube->player->fov * 0.5) / WIDTH;
	printf("Player angle: %f (devrait être ~1.5708 pour Nord)\n", cube->player->angle);
	printf("Player pos: (%.2f, %.2f)\n", cube->player->pos_x, cube->player->pos_y);
	printf("FOV: %f\n", cube->player->fov);
	x = WIDTH;
	while (x >= 0)
	{
		// Calculer l'angle pour ce rayon spécifique
		angle = cube->player->angle + (x - WIDTH * 0.5) * R_H;
		printf("angle = %f\n",angle);
		// Direction du rayon
		dir.x = cos(angle);
		dir.y = -sin(angle);
		// Position de départ (position du joueur)
		rayon.x = cube->player->pos_x;
		rayon.y = cube->player->pos_y;
		step = 0;
		while (step <= 1000)
		{
			rayon.x += dir.x ;
			rayon.y += dir.y ;
			// Vérifier si on touche un mur
			if (cube->map->final_grid[(int)rayon.y][(int)rayon.x] == '1')
			{
				printf("Rayon %d: mur trouvé à (%.2f, %.2f)\n", x, rayon.x,
					rayon.y);
				break;
			}
			step++;
		}
		x--;
	}
	return ;
}

void	render(t_game *cube)
{
	render_floor_ceilling(cube->img, cube->textures);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img_ptr, 0, 0);
	launch_rayon(cube);
}
