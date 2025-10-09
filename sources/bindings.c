/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:31:12 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/09 14:22:40 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


int	define_control(int keypress, t_game *cube)
{
	if (keypress == ESCAPE)
		free_exit(cube);
	else if (keypress == W)
	{
		cube->player->pos_y -= 0.5;
		printf("pos_x : %f  pos_y : %f\n",cube->player->pos_x, cube->player->pos_y);
		render(cube);
	}
	else if (keypress == S)
	{
		cube->player->pos_y += 0.5;
		printf("pos_x : %f  pos_y : %f\n",cube->player->pos_x, cube->player->pos_y);
		render(cube);
	}
	else if (keypress == A)
	{
		// cube->player->pos_x -= 0.5;
		cube->player->angle += M_PI / 4;
		printf("pos_x : %f  pos_y : %f\n",cube->player->pos_x, cube->player->pos_y);
		render(cube);
	}
	else if (keypress == D)
	{
		//cube->player->pos_x += 0.5;
		cube->player->angle -= M_PI / 4;
		printf("pos_x : %f  pos_y : %f\n",cube->player->pos_x, cube->player->pos_y);
		render(cube);
	}
	return (1);
}
