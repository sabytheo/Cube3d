/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:04:24 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/19 16:04:35 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	close_door(t_game *cube, float step_x, float step_y)
{
	int	pos_y;
	int	pos_x;

	pos_y = (int)(cube->player.pos_y);
	pos_x = (int)(cube->player.pos_x);
	if (cube->map.final_grid[(int)pos_y][(int)pos_x] != 'O')
	{
		if (cube->map.final_grid[(int)(pos_y + step_y)][pos_x] == 'O')
			cube->map.final_grid[(int)(pos_y + step_y)][pos_x] = 'C';
		else if (cube->map.final_grid[pos_y][(int)(pos_x + step_x)] == 'O')
			cube->map.final_grid[pos_y][(int)(pos_x + step_x)] = 'C';
	}
}

void	open_close_door(t_game *cube)
{
	float	step_y;
	float	step_x;
	int		pos_y;
	int		pos_x;

	pos_y = (int)cube->player.pos_y;
	pos_x = (int)cube->player.pos_x;
	step_y = -sin(cube->player.angle);
	step_x = cos(cube->player.angle);
	printf("%d\n", pos_x);
	printf("%d\n", pos_y);
	if (cube->key.e == true)
	{
		if (cube->map.final_grid[(int)(pos_y + step_y)][pos_x] == 'C')
		{
			cube->map.final_grid[(int)(pos_y + step_y)][pos_x] = 'O';
		}
		else if (cube->map.final_grid[(int)pos_y][(int)(pos_x + step_x)] == 'C')
			cube->map.final_grid[(int)pos_y][(int)(pos_x + step_x)] = 'O';
	}
	else if (cube->key.f == true)
		close_door(cube, step_x, step_y);
}
