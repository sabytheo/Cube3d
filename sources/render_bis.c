/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:53:07 by egache            #+#    #+#             */
/*   Updated: 2025/11/06 17:40:40 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cube.h"

/* OTHER ALGO ----------------------   */
// static void init_raycast(t_game *cube)
// {
// 	cube->raycast.base_height = 1;
// 	cube->raycast.R_H = 2 * tan(cube->player.fov * 0.5) / WIDTH;
// 	cube->raycast.d_plan = WIDTH / (2 * tan(cube->player.fov * 0.5));
// 	return;
// }

// static void get_distance_and_wallheight(t_game *cube, t_vector rayon)
// {
// 	cube->raycast.distance = sqrt(pow(rayon.x - cube->player.pos_x, 2) + pow(rayon.y - cube->player.pos_y, 2));
// 	cube->raycast.corrected_distance = cube->raycast.distance * cos(cube->raycast.angle - cube->player.angle);
// 	cube->raycast.wall_height = (cube->raycast.base_height * cube->raycast.d_plan) / cube->raycast.corrected_distance;
// }

// void raycast(t_game *cube, t_raycast *raycast)
// {
// 	t_vector ray;
// 	t_vector prev_ray;
// 	t_vector dir;
// 	int x;
// 	int mapX;
// 	int mapY;
// 	int prev_mapX;
// 	int prev_mapY;

// 	cube->raycast.dir = &dir;
// 	init_raycast(cube);
// 	x = 0;
// 	while (x <= WIDTH)
// 	{
// 		float camera_x = 2 * x / (float)WIDTH - 1;
// 		raycast->angle = cube->player.angle + atan(camera_x * tan(cube->player.fov / 2));
// 		dir.x = cos(raycast->angle) * 0.01;
// 		dir.y = -sin(raycast->angle) * 0.01;
// 		ray.x = cube->player.pos_x;
// 		ray.y = cube->player.pos_y;
// 		while (cube->map.final_grid[(int)ray.y][(int)ray.x] != '1')
// 		{
// 			prev_ray = ray;
// 			ray.x += dir.x;
// 			ray.y += dir.y;
// 		}
// 		mapX = (int)ray.x;
// 		mapY = (int)ray.y;
// 		prev_mapX = (int)prev_ray.x;
// 		prev_mapY = (int)prev_ray.y;
// 		get_distance_and_wallheight(cube, ray);
// 		if (prev_mapX != mapX)
// 		{
// 			if (dir.x >= 0)
// 			{
// 				render_wall(raycast->wall_height, cube, x, BLUE);
// 			}
// 			else
// 				render_wall(raycast->wall_height, cube, x, RED);
// 		}
// 		if (prev_mapY != mapY)
// 		{
// 			if (dir.y >= 0)
// 			{
// 				render_wall(raycast->wall_height, cube, x, GREEN);
// 			}
// 			else
// 				render_wall(raycast->wall_height, cube, x, PURPLE);
// 		}
// 		// render_wall(raycast->wall_height, cube, x, WHITE);
// 		//     render_wall(raycast->wall_height, cube, x, RED);
// 		x++;
// 	}
// 	return;
// }
/* OTHER ALGO ----------------------   */
