/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:28:58 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/11 17:48:24 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	camera_mouse_control(t_game *cube)
{
	int			mouse_x;
	int			mouse_y;
	int			mouvement_x;
	static int	old_x = WIDTH / 2;

	if (cube->key.tab)
	{
		mlx_mouse_hide(cube->mlx, cube->windows);
		mlx_mouse_get_pos(cube->mlx, cube->windows, &mouse_x, &mouse_y);
		mouvement_x = mouse_x - old_x;
		if (mouvement_x == 0)
			return ;
		cube->player.angle -= mouvement_x * MOUSE_SENSIBILITY
			* cube->player.rotation_speed * cube->delta_time;
		if (mouse_x < WIDTH * 0.1 || mouse_x > WIDTH * 0.9)
		{
			mlx_mouse_move(cube->mlx, cube->windows, WIDTH / 2, HEIGHT / 2);
			old_x = WIDTH / 2;
		}
		else
			old_x = mouse_x;
	}
	else
		mlx_mouse_show(cube->mlx, cube->windows);
}

void	update_delta_time(t_game *cube)
{
	struct timeval	current_time;
	double			time_spent;

	gettimeofday(&current_time, NULL);
	time_spent = (current_time.tv_sec - cube->last_frame.tv_sec)
		+ (current_time.tv_usec - cube->last_frame.tv_usec) / 1000000.0;
	if (time_spent > 0.1)
		time_spent = 0.1;
	cube->delta_time = time_spent;
	cube->last_frame = current_time;
}

int	is_hitting(float x, float y, t_game *cube)
{
	static const char	c[2] = {'1', 'C'};

	if (cube->map.final_grid[(int)(y + XBOX)][(int)(x + XBOX)] != c[0]
		&& cube->map.final_grid[(int)(y + XBOX)][(int)(x + XBOX)] != c[1])
	{
		if (cube->map.final_grid[(int)(y + XBOX)][(int)(x - XBOX)] != c[0]
			&& cube->map.final_grid[(int)(y + XBOX)][(int)(x - XBOX)] != c[1])
		{
			if (cube->map.final_grid[(int)(y - XBOX)][(int)(x + XBOX)] != c[0]
				&& cube->map.final_grid[(int)(y - XBOX)][(int)(x
					+ XBOX)] != c[1])
			{
				if (cube->map.final_grid[(int)(y - XBOX)][(int)(x
						- XBOX)] != c[0] && cube->map.final_grid[(int)(y
						- XBOX)][(int)(x - XBOX)] != c[1])
				{
					return (0);
				}
				return (1);
			}
			return (1);
		}
		return (1);
	}
	return (1);
}

int	press_key(int keypress, t_game *cube)
{
	if (keypress == MAJ)
		cube->key.maj = true;
	if (keypress == W)
		cube->key.w = true;
	if (keypress == S)
		cube->key.s = true;
	if (keypress == A)
		cube->key.a = true;
	if (keypress == D)
		cube->key.d = true;
	if (keypress == E)
		cube->key.e = true;
	if (keypress == F)
		cube->key.f = true;
	if (keypress == A_LEFT)
		cube->key.left = true;
	if (keypress == A_RIGHT)
		cube->key.right = true;
	if (keypress == ESCAPE)
		cube->key.escape = true;
	if (keypress == TAB)
		cube->key.tab = !cube->key.tab;
	return (0);
}

int	release_key(int keypress, t_game *cube)
{
	if (keypress == MAJ)
		cube->key.maj = false;
	if (keypress == W)
		cube->key.w = false;
	if (keypress == S)
		cube->key.s = false;
	if (keypress == A)
		cube->key.a = false;
	if (keypress == D)
		cube->key.d = false;
	if (keypress == E)
		cube->key.e = false;
	if (keypress == F)
		cube->key.f = false;
	if (keypress == A_LEFT)
		cube->key.left = false;
	if (keypress == A_RIGHT)
		cube->key.right = false;
	if (keypress == ESCAPE)
		cube->key.escape = false;
	return (0);
}
