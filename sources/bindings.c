/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:31:12 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/30 08:43:17 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_hitting(float x, float y, t_game *cube, char c)
{
	if (cube->map->final_grid[(int)(y +	XBOX)][(int)(x + XBOX)] != c)
	{
		if (cube->map->final_grid[(int)(y + XBOX)][(int)(x - XBOX)] != c)
		{
			if (cube->map->final_grid[(int)(y - XBOX)][(int)(x + XBOX)] != c)
			{
				if (cube->map->final_grid[(int)(y - XBOX)][(int)(x - XBOX)] != c)
				{
					return (0);
				}
				return (-1);
			}
			return (-1);
		}
		return (-1);
	}
	return (-1);
}

static void	press_W_S( t_game *cube, float newpos_x,
		float newpos_y)
{
	float step_x;
	float step_y;

	step_x = cos(cube->player->angle) * cube->player->speed;
	step_y = -sin(cube->player->angle) * cube->player->speed;
	if (cube->key->w == true)
	{
		newpos_x += step_x;
		newpos_y += step_y;
		if (is_hitting(newpos_x, newpos_y, cube, '1') == 0)
		{
			cube->player->pos_x = newpos_x ;
			cube->player->pos_y = newpos_y ;
		}
		else
		{
			if (is_hitting(cube->player->pos_x, newpos_y, cube, '1') == 0)
				cube->player->pos_y = newpos_y ;
			else
			{
				if (is_hitting(newpos_x, cube->player->pos_y, cube, '1') == 0)
					cube->player->pos_x = newpos_x ;
			}
		}
	}
	if (cube->key->s == true)
	{
		newpos_x -= cos(cube->player->angle) * cube->player->speed;
		newpos_y -= -sin(cube->player->angle) * cube->player->speed;
		if (is_hitting(newpos_x, newpos_y, cube, '1') == 0)
		{
			cube->player->pos_x = newpos_x;
			cube->player->pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player->pos_x, newpos_y, cube, '1') == 0)
				cube->player->pos_y = newpos_y ;
			else
			{
				if (is_hitting(newpos_x, cube->player->pos_y, cube, '1') == 0)
					cube->player->pos_x = newpos_x ;
			}
		}
	}
	return ;
}

static void	press_A_D( t_game *cube, float newpos_x,
			float newpos_y)
{
	float step_x;
	float step_y;

	if (cube->key->a == true)
	{
		step_x = cos(cube->player->angle - (M_PI * 0.5)) * cube->player->speed;
		step_y = -sin(cube->player->angle - (M_PI * 0.5)) * cube->player->speed;
		newpos_x += step_x;
		newpos_y += step_y;
		if (is_hitting(newpos_x, newpos_y, cube, '1') == 0)
		{
			cube->player->pos_x = newpos_x;
			cube->player->pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player->pos_x, newpos_y, cube, '1') == 0)
				cube->player->pos_y = newpos_y ;
			else
			{
				if (is_hitting(newpos_x, cube->player->pos_y, cube, '1') == 0)
					cube->player->pos_x = newpos_x ;
			}
		}
	}
	if (cube->key->d == true)
	{
		step_x = cos(cube->player->angle + (M_PI * 0.5)) * cube->player->speed;
		step_y = -sin(cube->player->angle + (M_PI * 0.5)) * cube->player->speed;
		newpos_x += step_x;
		newpos_y += step_y;
		if (is_hitting(newpos_x , newpos_y, cube, '1') == 0)
		{
			cube->player->pos_x = newpos_x;
			cube->player->pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player->pos_x, newpos_y, cube, '1') == 0)
				cube->player->pos_y = newpos_y ;
			else
			{
				if (is_hitting(newpos_x, cube->player->pos_y, cube, '1') == 0)
					cube->player->pos_x = newpos_x ;
			}
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
	if (keypress == E)
		cube->key->e= true;
	if (keypress == F)
		cube->key->f= true;
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
	if (keypress == E)
		cube->key->e= false;
	if (keypress == F)
		cube->key->f= false;
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

	newpos_x = cube->player->pos_x;
	newpos_y = cube->player->pos_y;
	if (cube->key->escape == true)
		free_exit(cube);
	if (cube->key->w == true || cube->key->s == true)
		press_W_S(cube, newpos_x, newpos_y);
	if (cube->key->a == true || cube->key->d == true)
		press_A_D(cube, newpos_x, newpos_y);
	if (cube->key->left == true)
		cube->player->angle -= DEG_TO_RAD * 5;
	if (cube->key->right == true)
		cube->player->angle += DEG_TO_RAD * 5;
	render(cube);
	return (0);
}
