/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reef.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:00:03 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/28 17:03:49 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

int	free_exit(t_game *cube, int state)
{
	if (cube->windows)
		mlx_destroy_window(cube->mlx, cube->windows);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	if (cube->textures->wall)
		free_tab(cube->textures->wall);
	if (cube->map->grid)
		free_tab(cube->map->grid);
	if(cube->map->width)
		free(cube->map->width);
	if(cube->map)
		free(cube->map);
	if(cube->textures)
		free(cube->textures);
	exit(state);
}
