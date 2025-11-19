/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:07:01 by egache            #+#    #+#             */
/*   Updated: 2025/11/19 16:07:41 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void join_threads(t_game *cube, t_cube_thread **cube_thread)
{
	int i;

	i = 0;
	while (i < cube->nb_cores)
	{
		if (cube_thread[i])
		{
			pthread_join(cube_thread[i]->thread, NULL);
			for (int j = 0; j < cube->map.grid_height; j++)
				free(cube_thread[i]->map.final_grid[j]);
			free(cube_thread[i]->map.final_grid);
			free(cube_thread[i]);
		}
		i++;
	}
}

t_cube_thread *init_thread(t_game *cube, t_cube_thread *cube_thread, int column_size, int column_start)
{
	int				i;

	cube_thread = malloc(1 * sizeof(t_cube_thread));
	if (column_start == 0)
		cube_thread->width_start = column_start;
	else
		cube_thread->width_start = column_start + 1;
	cube_thread->width_end = column_start + column_size;
	cube_thread->cube = cube;
	cube_thread->map = cube->map;
	cube_thread->textures = cube->textures;
	cube_thread->raycast = cube->raycast;
	cube_thread->map.final_grid = malloc(sizeof(char *)
	* cube->map.grid_height);
	i = 0;
	while (i < cube->map.grid_height)
	{
		cube_thread->map.final_grid[i] = ft_strdup(cube->map.final_grid[i]);
		i++;
	}
	return(cube_thread);
}

void launch_threads(t_game *cube)
{
	t_cube_thread	*cube_thread[cube->nb_cores];
	int				column_size;
	int				column_start;
	int				i;

	column_size = WIDTH / cube->nb_cores;
	column_start = 0;
	i = 0;
	while (i < cube->nb_cores)
	{
		cube_thread[i] = init_thread(cube, cube_thread[i], column_size, column_start);
		if (pthread_create(&cube_thread[i]->thread, NULL, &raycast,
				cube_thread[i]))
			return ;
		column_start += column_size;
		i++;
	}
	join_threads(cube, cube_thread);
}
