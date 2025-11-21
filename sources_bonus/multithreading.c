/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:07:01 by egache            #+#    #+#             */
/*   Updated: 2025/11/21 13:57:50 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	free_threads_tab(t_game *cube, t_cube_thread **cube_thread)
{
	int	i;
	int	j;

	i = 0;
	while (cube_thread[i])
	{
		j = 0;
		while (j < cube->map.grid_height)
		{
			if (cube_thread[i]->map.final_grid[j])
				free(cube_thread[i]->map.final_grid[j]);
			j++;
		}
		if (cube_thread[i]->map.final_grid)
			free(cube_thread[i]->map.final_grid);
		if (cube_thread[i])
			free(cube_thread[i]);
		i++;
	}
	free(cube_thread);
}

void	join_threads(t_game *cube, t_cube_thread **cube_thread)
{
	int	i;
	int	j;

	i = 0;
	while (i < cube->nb_cores)
	{
		if (cube_thread[i])
		{
			pthread_join(cube_thread[i]->thread, NULL);
			j = 0;
			while (j < cube->map.grid_height)
			{
				if (cube_thread[i]->map.final_grid[j])
					free(cube_thread[i]->map.final_grid[j]);
				j++;
			}
			if (cube_thread[i]->map.final_grid)
				free(cube_thread[i]->map.final_grid);
			if (cube_thread[i])
				free(cube_thread[i]);
		}
		i++;
	}
	if (cube_thread)
		free(cube_thread);
}

static int	init_thread_grid(t_game *cube, t_cube_thread *cube_thread)
{
	int	i;

	cube_thread->map.final_grid = malloc(sizeof(char *)
			* cube->map.grid_height);
	if (!cube_thread->map.final_grid)
		return (-1);
	i = 0;
	while (i < cube->map.grid_height)
	{
		cube_thread->map.final_grid[i] = ft_strdup(cube->map.final_grid[i]);
		if (!cube_thread->map.final_grid[i])
		{
			free_tab(cube_thread->map.final_grid);
			return (-1);
		}
		i++;
	}
	return (0);
}

t_cube_thread	*init_thread(t_game *cube, t_cube_thread *cube_thread,
		int column_size, int column_start)
{
	cube_thread = malloc(1 * sizeof(t_cube_thread));
	if (!cube_thread)
		return (NULL);
	if (column_start == 0)
		cube_thread->width_start = column_start;
	else
		cube_thread->width_start = column_start + 1;
	cube_thread->width_end = column_start + column_size;
	cube_thread->cube = cube;
	cube_thread->map = cube->map;
	cube_thread->textures = cube->textures;
	cube_thread->raycast = cube->raycast;
	if (init_thread_grid(cube, cube_thread) < 0)
	{
		free(cube_thread);
		return (NULL);
	}
	return (cube_thread);
}

int	launch_threads(t_game *cube, t_cube_thread **cube_thread)
{
	int	column_size;
	int	column_start;
	int	i;

	column_size = WIDTH / cube->nb_cores;
	column_start = 0;
	i = 0;
	while (i < cube->nb_cores)
	{
		cube_thread[i] = init_thread(cube, cube_thread[i], column_size,
				column_start);
		if (cube_thread[i] == NULL)
			return (-1);
		if (pthread_create(&cube_thread[i]->thread, NULL, &raycast,
				cube_thread[i]))
			return (-1);
		column_start += column_size;
		i++;
	}
	join_threads(cube, cube_thread);
	if (cube->running == false)
		free_exit(cube);
	return (0);
}
