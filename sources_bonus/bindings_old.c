/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:31:12 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/08 20:13:35 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	press_s(t_game *cube, float newpos_x, float newpos_y)
{
	float	step_x;
	float	step_y;

	step_x = cos(cube->player.angle) * cube->player.speed * cube->delta_time;
	step_y = -sin(cube->player.angle) * cube->player.speed * cube->delta_time;
	if (cube->key.s == true)
	{
		newpos_x -= step_x;
		newpos_y -= step_y;
		if (is_hitting(newpos_x, newpos_y, cube) == 0)
		{
			cube->player.pos_x = newpos_x;
			cube->player.pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player.pos_x, newpos_y, cube) == 0)
				cube->player.pos_y = newpos_y;
			else
			{
				if (is_hitting(newpos_x, cube->player.pos_y, cube) == 0)
					cube->player.pos_x = newpos_x;
			}
		}
	}
}

static void	press_w(t_game *cube, float newpos_x, float newpos_y)
{
	float	step_x;
	float	step_y;

	step_x = cos(cube->player.angle) * cube->player.speed * cube->delta_time;
	step_y = -sin(cube->player.angle) * cube->player.speed * cube->delta_time;
	if (cube->key.w == true)
	{
		newpos_x += step_x;
		newpos_y += step_y;
		if (is_hitting(newpos_x, newpos_y, cube) == 0)
		{
			cube->player.pos_x = newpos_x;
			cube->player.pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player.pos_x, newpos_y, cube) == 0)
				cube->player.pos_y = newpos_y;
			else
			{
				if (is_hitting(newpos_x, cube->player.pos_y, cube) == 0)
					cube->player.pos_x = newpos_x;
			}
		}
	}
}

static void	press_d(t_game *cube, float newpos_x, float newpos_y)
{
	float	step_x;
	float	step_y;

	step_x = cos(cube->player.angle - (M_PI * 0.5)) * cube->player.speed
		* cube->delta_time;
	step_y = -sin(cube->player.angle - (M_PI * 0.5)) * cube->player.speed
		* cube->delta_time;
	newpos_x += step_x;
	newpos_y += step_y;
	if (cube->key.d == true)
	{
		if (is_hitting(newpos_x, newpos_y, cube) == 0)
		{
			cube->player.pos_x = newpos_x;
			cube->player.pos_y = newpos_y;
		}
		else
		{
			if (is_hitting(cube->player.pos_x, newpos_y, cube) == 0)
				cube->player.pos_y = newpos_y;
			else
			{
				if (is_hitting(newpos_x, cube->player.pos_y, cube) == 0)
					cube->player.pos_x = newpos_x;
			}
		}
	}
}

static void	press_a(t_game *cube, float newpos_x, float newpos_y)
{
	float	step_x;
	float	step_y;

	step_x = cos(cube->player.angle + (M_PI * 0.5)) * cube->player.speed
		* cube->delta_time;
	step_y = -sin(cube->player.angle + (M_PI * 0.5)) * cube->player.speed
		* cube->delta_time;
	newpos_x += step_x;
	newpos_y += step_y;
	if (is_hitting(newpos_x, newpos_y, cube) == 0 && is_hitting(newpos_x,
			newpos_y, cube) == 0)
	{
		cube->player.pos_x = newpos_x;
		cube->player.pos_y = newpos_y;
	}
	else
	{
		if (is_hitting(cube->player.pos_x, newpos_y, cube) == 0)
			cube->player.pos_y = newpos_y;
		else
		{
			if (is_hitting(newpos_x, cube->player.pos_y, cube) == 0)
				cube->player.pos_x = newpos_x;
		}
	}
}

void	press_E_F(t_game *cube)
{
	float	step_y;
	float	step_x;

	step_y = -sin(cube->player.angle);
	step_x = cos(cube->player.angle);
	if (cube->key.e == true)
	{
		if (cube->map.final_grid[(int)(cube->player.pos_y
				+ step_y)][(int)cube->player.pos_x] == 'C')
		{
			cube->map.final_grid[(int)(cube->player.pos_y
					+ step_y)][(int)cube->player.pos_x] = 'O';
		}
		else if (cube->map.final_grid[(int)cube->player.pos_y][(int)(cube->player.pos_x
				+ step_x)] == 'C')
			cube->map.final_grid[(int)cube->player.pos_y][(int)(cube->player.pos_x
					+ step_x)] = 'O';
	}
	else if (cube->key.f == true)
	{
		if (cube->map.final_grid[(int)cube->player.pos_y][(int)(cube->player.pos_x)] != 'O')
		{
			if (cube->map.final_grid[(int)(cube->player.pos_y
					+ step_y)][(int)cube->player.pos_x] == 'O')
				cube->map.final_grid[(int)(cube->player.pos_y
						+ step_y)][(int)cube->player.pos_x] = 'C';
			else if (cube->map.final_grid[(int)cube->player.pos_y][(int)(cube->player.pos_x
					+ step_x)] == 'O')
				cube->map.final_grid[(int)cube->player.pos_y][(int)(cube->player.pos_x
						+ step_x)] = 'C';
		}
	}
}

int	define_control(t_game *cube)
{
	float	newpos_x;
	float	newpos_y;

	update_delta_time(cube);
	newpos_x = cube->player.pos_x;
	newpos_y = cube->player.pos_y;
	if (cube->key.escape == true)
		free_exit(cube);
	if (cube->key.d == true)
		press_d(cube, newpos_x, newpos_y);
	if (cube->key.a == true)
		press_a(cube, newpos_x, newpos_y);
	if (cube->key.w == true)
		press_w(cube, newpos_x, newpos_y);
	if (cube->key.s == true)
		press_s(cube, newpos_x, newpos_y);
	if (cube->key.e == true || cube->key.f == true)
		press_E_F(cube);
	if (cube->key.right == true)
		cube->player.angle -= cube->player.rotation_speed * cube->delta_time ;
	if (cube->key.left == true)
		cube->player.angle += cube->player.rotation_speed * cube->delta_time ;
	render(cube);
	return (0);
}
