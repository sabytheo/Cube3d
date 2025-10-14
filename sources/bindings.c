/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:31:12 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/14 16:41:30 by tsaby            ###   ########.fr       */
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

static void	press_W_S( t_game *cube, float newpos_x,
		float newpos_y)
{
	if (cube->key->w == true)
	{
		// printf(" cos mes couilles %f\n",cos(cube->player->angle) * SPEED);
		newpos_x += cos(cube->player->angle) * SPEED;
		newpos_y += -sin(cube->player->angle) * SPEED;
		if (is_valid_coordinate((int)newpos_x, (int)newpos_y, cube) == 0)
		{
			cube->player->pos_x = newpos_x;
			cube->player->pos_y = newpos_y;
			render(cube);
		}
	}
	if (cube->key->s == true)
	{
		// printf(" cos mes couilles %f\n",cos(cube->player->angle) * SPEED);
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

static void	press_A_D( t_game *cube, float newpos_x,
			float newpos_y)
{
	if (cube->key->a == true)
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
	if (cube->key->d == true)
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
int press_key(int keypress, t_game *cube)
{
	if (keypress == W)
		cube->key->w = true;
	if (keypress == S)
		cube->key->s= true;
	if (keypress == A)
		cube->key->a= true;
	if (keypress == D)
		cube->key->d= true;
	if (keypress == A_LEFT)
		cube->key->left= true;
	if (keypress == A_RIGHT)
		cube->key->right= true;
	if (keypress == ESCAPE)
		cube->key->escape= true;
	return (0);
}

int release_key(int keypress, t_game *cube)
{
	if (keypress == W)
		cube->key->w = false;
	if (keypress == S)
		cube->key->s= false;
	if (keypress == A)
		cube->key->a= false;
	if (keypress == D)
		cube->key->d= false;
	if (keypress == A_LEFT)
		cube->key->left= false;
	if (keypress == A_RIGHT)
		cube->key->right= false;
	if (keypress == ESCAPE)
		cube->key->escape= false;
	return (0);
}

int	define_control(t_game *cube)
{
	float			newpos_x;
	float			newpos_y;
	const double	DEG_TO_RAD = M_PI * (1.0 / 180.0);

	// printf(" keypress %d\n",keypress);
	newpos_x = cube->player->pos_x;
	newpos_y = cube->player->pos_y;
	if (cube->key->escape == true)
		free_exit(cube);
	if (cube->key->w == true || cube->key->s == true)
		press_W_S(cube, newpos_x, newpos_y);
	if (cube->key->a == true || cube->key->d == true)
		press_A_D(cube, newpos_x, newpos_y);
	if (cube->key->left == true)
	{
		cube->player->angle -= DEG_TO_RAD * 2;
		render(cube);
	}
	if (cube->key->right == true)
	{
		cube->player->angle += DEG_TO_RAD * 2;
		render(cube);
	}
	return (0) ;
}
