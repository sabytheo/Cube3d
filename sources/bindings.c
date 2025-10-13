/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:31:12 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/13 17:44:06 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_valid_coordinate(int x, int y, t_game *cube)
{
	if (cube->map->final_grid[y][x] == 'V')
	{
		return (0);
	}
	return (-1);
}

static void	press_W_S(int keypress, t_game *cube, float newpos_x,
		float newpos_y)
{
	if (keypress == W)
	{
		printf(" cos mes couilles %f\n",cos(cube->player->angle) * SPEED);
		newpos_x += cos(cube->player->angle) * SPEED;
		newpos_y += -sin(cube->player->angle) * SPEED;
		if (is_valid_coordinate((int)newpos_x, (int)newpos_y, cube) == 0)
		{
			cube->player->pos_x = newpos_x;
			cube->player->pos_y = newpos_y;
			render(cube);
		}
	}
	if (keypress == S)
	{
		printf(" cos mes couilles %f\n",cos(cube->player->angle) * SPEED);
		newpos_x -= cos(cube->player->angle) * SPEED;
		newpos_y -= -sin(cube->player->angle) * SPEED;
		if (is_valid_coordinate((int)newpos_x, (int)newpos_y, cube) == 0)
		{
			cube->player->pos_x = newpos_x;
			cube->player->pos_y = newpos_y;
			render(cube);
		}
	}
	return ;
}

static void	press_A_D(int keypress, t_game *cube, float newpos_x,
			float newpos_y)
{
	if (keypress == A)
	{
		newpos_x += cos(cube->player->angle - (M_PI * 0.5)) * SPEED;
		newpos_y += -sin(cube->player->angle - (M_PI * 0.5)) * SPEED;
		if (is_valid_coordinate((int)newpos_x, (int)newpos_y, cube) == 0)
		{
			cube->player->pos_x = newpos_x;
			cube->player->pos_y = newpos_y;
			render(cube);
		}
	}
	if (keypress == D)
	{
		newpos_x += cos(cube->player->angle + (M_PI * 0.5)) * SPEED;
		newpos_y += -sin(cube->player->angle + (M_PI * 0.5)) * SPEED;
		if (is_valid_coordinate((int)newpos_x, (int)newpos_y, cube) == 0)
		{
			cube->player->pos_x = newpos_x;
			cube->player->pos_y = newpos_y;
			render(cube);
		}
	}
	return ;
}

int	define_control(int keypress, t_game *cube)
{
	float			newpos_x;
	float			newpos_y;
	const double	DEG_TO_RAD = M_PI * (1.0 / 180.0);

	printf(" keypress %d\n",keypress);
	newpos_x = cube->player->pos_x;
	newpos_y = cube->player->pos_y;
	if (keypress == ESCAPE)
		free_exit(cube);
	if (keypress == W || keypress == S)
		press_W_S(keypress, cube, newpos_x, newpos_y);
	if (keypress == A || keypress == D)
		press_A_D(keypress, cube, newpos_x, newpos_y);
	if (keypress == A_LEFT)
	{
		cube->player->angle -= DEG_TO_RAD;
		render(cube);
	}
	if (keypress == A_RIGHT)
	{
		cube->player->angle += DEG_TO_RAD;
		render(cube);
	}
	return (1);
}
