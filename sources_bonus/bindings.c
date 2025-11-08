/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:31:12 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/08 22:07:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"


static void close_door(t_game *cube, float step_x, float step_y)
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
        close_door(cube,step_x,step_y);
}

static void check_move_x_or_move_y(t_game *cube,float move_x , float move_y)
{
    float newpos_x;
    float newpos_y;

    newpos_x = cube->player.pos_x + move_x;
	newpos_y = cube->player.pos_y;
		if (!is_hitting(newpos_x, newpos_y, cube) && !is_hitting(newpos_x,
				newpos_y, cube) && !is_hitting(newpos_x, newpos_y, cube)
			&& !is_hitting(newpos_x, newpos_y, cube))
			cube->player.pos_x = newpos_x;
		else
		{
			newpos_x = cube->player.pos_x;
			newpos_y = cube->player.pos_y + move_y;
			if (!is_hitting(newpos_x, newpos_y, cube) && !is_hitting(newpos_x,
					newpos_y, cube) && !is_hitting(newpos_x, newpos_y, cube)
				&& !is_hitting(newpos_x, newpos_y, cube))
				cube->player.pos_y = newpos_y;
		}
}

static void	apply_movement(t_game *cube, float move_x, float move_y)
{
	float	newpos_x;
	float	newpos_y;

	newpos_x = cube->player.pos_x + move_x;
	newpos_y = cube->player.pos_y + move_y;
	if (!is_hitting(newpos_x, newpos_y, cube) && !is_hitting(newpos_x, newpos_y,
			cube) && !is_hitting(newpos_x, newpos_y, cube)
		&& !is_hitting(newpos_x, newpos_y, cube))
	{
		cube->player.pos_x = newpos_x;
		cube->player.pos_y = newpos_y;
	}
	else
		check_move_x_or_move_y(cube,move_x,move_y);
}

static void add_forward_and_backward(t_game*cube, float *step_x, float *step_y)
{

    if (cube->key.w)
	{
		*step_x += cos(cube->player.angle) * cube->player.speed
			* cube->delta_time;
		*step_y += -sin(cube->player.angle) * cube->player.speed
			* cube->delta_time;
	}
	if (cube->key.s)
	{
		*step_x -= cos(cube->player.angle) * cube->player.speed
			* cube->delta_time;
		*step_y -= -sin(cube->player.angle) * cube->player.speed
			* cube->delta_time;
	}
}

static void	calculate_movement(t_game *cube, float *move_x, float *move_y)
{
	float	step_x;
	float	step_y;

	step_x = 0;
	step_y = 0;
    add_forward_and_backward(cube,&step_x,&step_y);
	if (cube->key.a)
	{
		step_x += cos(cube->player.angle + M_PI * 0.5) * cube->player.speed
			* cube->delta_time;
		step_y += -sin(cube->player.angle + M_PI * 0.5) * cube->player.speed
			* cube->delta_time;
	}
	if (cube->key.d)
	{
		step_x += cos(cube->player.angle - M_PI * 0.5) * cube->player.speed
			* cube->delta_time;
		step_y += -sin(cube->player.angle - M_PI * 0.5) * cube->player.speed
			* cube->delta_time;
	}
	*move_x = step_x;
	*move_y = step_y;
}

int	define_control(t_game *cube)
{
	float	move_x;
	float	move_y;

	move_x = 0;
	move_y = 0;
	update_delta_time(cube);
	if (cube->key.escape == true)
		free_exit(cube);
	if (cube->key.maj == true)
		cube->player.speed = 0.8;
    else if  (cube->key.maj == false)
		cube->player.speed = 0.5;
	calculate_movement(cube, &move_x, &move_y);
	apply_movement(cube, move_x, move_y);
	if (cube->key.e == true || cube->key.f == true)
		press_E_F(cube);
	if (cube->key.right == true)
		cube->player.angle -= cube->player.rotation_speed * cube->delta_time;
	if (cube->key.left == true)
		cube->player.angle += cube->player.rotation_speed * cube->delta_time;
	render(cube);
	return (0);
}
