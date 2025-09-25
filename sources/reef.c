/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reef.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:37:43 by tsaby             #+#    #+#             */
/*   Updated: 2025/09/25 18:10:14 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_tab(char **tab)
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

// static void	free_int_tab(int *tab)
// {
// 	int	i;

// 	i = 0;
// 	if (tab)
// 	{
// 		while (tab[i])
// 		{
// 			free(tab[i]);
// 			i++;
// 		}
// 		free(tab);
// 	}
// }

int	free_exit(t_game *cube)
{
	if (cube->windows)
		mlx_destroy_window(cube->mlx, cube->windows);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	if (cube->map->grid)
		free_tab(cube->map->grid);
	if (cube->textures->NO)
		free(cube->textures->NO);
	if (cube->textures->SO)
		free(cube->textures->SO);
	if (cube->textures->WE)
		free(cube->textures->WE);
	if (cube->textures->EA)
		free(cube->textures->EA);
	// free(cube->textures->ceiling);
	// free(cube->textures->floor);
	if (cube->textures)
		free(cube->textures);
	if(cube->map->width)
		free(cube->map->width);
	if (cube->map)
		free(cube->map);
	exit(0);
}
