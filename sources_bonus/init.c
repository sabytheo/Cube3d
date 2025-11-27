/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:44:25 by egache            #+#    #+#             */
/*   Updated: 2025/11/27 18:24:35 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	init_values(t_game *cube)
{
	cube->nb_cores = sysconf(_SC_NPROCESSORS_ONLN);
	cube->player.speed = 1;
	cube->player.rotation_speed = 1;
	cube->player.fov = M_PI / 3;
	cube->running = true;
	pthread_mutex_init(&cube->running_lock, NULL);
	cube->last_mouse_pos_x = WIDTH / 2;
	cube->delta_time = 0.016;
	cube->raycast.base_height = 1;
	cube->raycast.d_plan = WIDTH / (2 * tan(cube->player.fov * 0.5));
}
