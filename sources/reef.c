/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reef.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:37:43 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:38:35 by egache           ###   ########.fr       */
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

static void	destroy_image(t_game *cube)
{
	if (cube->textures.EA_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.EA_img.img);
	if (cube->img->img)
		mlx_destroy_image(cube->mlx, cube->img->img);
	if (cube->textures.NO_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.NO_img.img);
	if (cube->textures.SO_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.SO_img.img);
	if (cube->textures.WE_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.WE_img.img);
	return ;
}

static void	clean_textures(t_game *cube)
{
	if (cube->textures.NO)
		free(cube->textures.NO);
	if (cube->textures.SO)
		free(cube->textures.SO);
	if (cube->textures.WE)
		free(cube->textures.WE);
	if (cube->textures.EA)
		free(cube->textures.EA);
	return ;
}

static void	clean_struct(t_game *cube)
{
	if (cube->map)
		free(cube->map);
	if (cube->img)
		free(cube->img);
	if (cube->raycast->dir)
		free(cube->raycast->dir);
	if (cube->raycast)
		free(cube->raycast);
	return ;
}

int	free_exit(t_game *cube)
{
	if (cube->windows)
		mlx_destroy_window(cube->mlx, cube->windows);
	destroy_image(cube);
	clean_textures(cube);
	if (cube->map->grid)
		free_tab(cube->map->grid);
	if (cube->map->final_grid)
		free_tab(cube->map->final_grid);
	if (cube->map->width)
		free(cube->map->width);
	clean_struct(cube);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	exit(0);
}
