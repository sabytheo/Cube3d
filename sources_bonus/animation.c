/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:33:22 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/21 17:43:31 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	update_texture_animation(t_game *cube)
{
	struct timeval	current_time;
	double			elapsed_time;
	const double	frame_duration = 1;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - cube->textures.last_frame_time.tv_sec)
		+ (current_time.tv_usec - cube->textures.last_frame_time.tv_usec)
		/ 1000000.0;
	if (elapsed_time >= frame_duration)
	{
		cube->textures.current_frame = (cube->textures.current_frame + 1) % 6;
		cube->textures.last_frame_time = current_time;
	}
}
