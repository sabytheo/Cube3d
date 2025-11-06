/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:31:12 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:23:56 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	press_s(t_game *cube, float newpos_x, float newpos_y)
{
	float	step_x;
	float	step_y;

	step_x = cos(cube->player.angle) * cube->player.speed;
	step_y = -sin(cube->player.angle) * cube->player.speed;
	if (cube->key->s == true)
	{
		newpos_x -= cos(cube->player.angle) * cube->player.speed;
		newpos_y -= -sin(cube->player.angle) * cube->player.speed;
		if (is_hitting(newpos_x, newpos_y, cube, '1') == 0)
		{
			cube->player.pos_x = newpos_x;
			cube->player.pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player.pos_x, newpos_y, cube, '1') == 0)
				cube->player.pos_y = newpos_y;
			else
			{
				if (is_hitting(newpos_x, cube->player.pos_y, cube, '1') == 0)
					cube->player.pos_x = newpos_x;
			}
		}
	}
}

static void	press_w(t_game *cube, float newpos_x, float newpos_y)
{
	float	step_x;
	float	step_y;

	step_x = cos(cube->player.angle) * cube->player.speed;
	step_y = -sin(cube->player.angle) * cube->player.speed;
	if (cube->key->w == true)
	{
		newpos_x += step_x;
		newpos_y += step_y;
		if (is_hitting(newpos_x, newpos_y, cube, '1') == 0)
		{
			cube->player.pos_x = newpos_x;
			cube->player.pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player.pos_x, newpos_y, cube, '1') == 0)
				cube->player.pos_y = newpos_y;
			else
			{
				if (is_hitting(newpos_x, cube->player.pos_y, cube, '1') == 0)
					cube->player.pos_x = newpos_x;
			}
		}
	}
}

static void	press_d(t_game *cube, float newpos_x, float newpos_y)
{
	float	step_x;
	float	step_y;

	step_x = cos(cube->player.angle - (M_PI * 0.5)) * cube->player.speed;
	step_y = -sin(cube->player.angle - (M_PI * 0.5)) * cube->player.speed;
	newpos_x += step_x;
	newpos_y += step_y;
	if (cube->key->d == true)
	{
		if (is_hitting(newpos_x, newpos_y, cube, '1') == 0)
		{
			cube->player.pos_x = newpos_x;
			cube->player.pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player.pos_x, newpos_y, cube, '1') == 0)
				cube->player.pos_y = newpos_y;
			else
			{
				if (is_hitting(newpos_x, cube->player.pos_y, cube, '1') == 0)
					cube->player.pos_x = newpos_x;
			}
		}
	}
}

static void	press_a(t_game *cube, float newpos_x, float newpos_y)
{
	float	step_x;
	float	step_y;

	step_x = cos(cube->player.angle + (M_PI * 0.5)) * cube->player.speed;
	step_y = -sin(cube->player.angle + (M_PI * 0.5)) * cube->player.speed;
	newpos_x += step_x;
	newpos_y += step_y;
	if (cube->key->a == true)
	{
		if (is_hitting(newpos_x, newpos_y, cube, '1') == 0)
		{
			cube->player.pos_x = newpos_x;
			cube->player.pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player.pos_x, newpos_y, cube, '1') == 0)
				cube->player.pos_y = newpos_y;
			else
			{
				if (is_hitting(newpos_x, cube->player.pos_y, cube, '1') == 0)
					cube->player.pos_x = newpos_x;
			}
		}
	}
}

int	define_control(t_game *cube)
{
	float			newpos_x;
	float			newpos_y;

	newpos_x = cube->player.pos_x;
	newpos_y = cube->player.pos_y;
	if (cube->key->escape == true)
		free_exit(cube);
	if (cube->key->d == true)
		press_d(cube, newpos_x, newpos_y);
	if (cube->key->a == true)
		press_a(cube, newpos_x, newpos_y);
	if (cube->key->w == true)
		press_w(cube, newpos_x, newpos_y);
	if (cube->key->s == true)
		press_s(cube, newpos_x, newpos_y);
	if (cube->key->right == true)
		cube->player.angle -= DEG_TO_RAD * 5;
	if (cube->key->left == true)
		cube->player.angle += DEG_TO_RAD * 5;
	render(cube);
	return (0);
}
