/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:04:20 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/27 13:41:34 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"


static void	move_forward(t_game *cube, float speed)
{
    float   new_x;
    float   new_y;

    new_x = cube->player->pos_x + cos(cube->player->angle) * speed;
    new_y = cube->player->pos_y + sin(cube->player->angle) * speed;
    if (cube->map->grid[(int)new_y][(int)new_x] != '1')
    {
        cube->player->pos_x = new_x;
        cube->player->pos_y = new_y;
    }
}

static void	move_backward(t_game *cube, float speed)
{
    float   new_x;
    float   new_y;

    new_x = cube->player->pos_x - cos(cube->player->angle) * speed;
    new_y = cube->player->pos_y - sin(cube->player->angle) * speed;
    if (cube->map->grid[(int)new_y][(int)new_x] != '1')
    {
        cube->player->pos_x = new_x;
        cube->player->pos_y = new_y;
    }
}

int define_control(int keypress, t_game *cube)
{
    float   move_speed;
    float   rot_speed;

    move_speed = 0.1;
    rot_speed = 0.05;
    if (keypress == ESCAPE)
        free_exit(cube);
    if (keypress == W)
        move_forward(cube, move_speed);
    if (keypress == S)
        move_backward(cube, move_speed);
    if (keypress == A)
        cube->player->angle -= rot_speed;
    if (keypress == D)
        cube->player->angle += rot_speed;
    return (0);}
