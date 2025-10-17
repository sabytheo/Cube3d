/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reef.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:37:43 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/17 13:53:52 by egache           ###   ########.fr       */
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
	if (cube->textures.EA_img.img_ptr)
		mlx_destroy_image(cube->mlx, cube->textures.EA_img.img_ptr);
	if (cube->img->img_ptr)
		mlx_destroy_image(cube->mlx, cube->img->img_ptr);
	if (cube->textures.NO_img.img_ptr)
		mlx_destroy_image(cube->mlx, cube->textures.NO_img.img_ptr);
	if (cube->textures.SO_img.img_ptr)
		mlx_destroy_image(cube->mlx, cube->textures.SO_img.img_ptr);
	if (cube->textures.WE_img.img_ptr)
		mlx_destroy_image(cube->mlx, cube->textures.WE_img.img_ptr);
	if (cube->map->grid)
		free_tab(cube->map->grid);
	if (cube->map->final_grid)
		free_tab(cube->map->final_grid);
	if (cube->textures.NO)
		free(cube->textures.NO);
	if (cube->textures.SO)
		free(cube->textures.SO);
	if (cube->textures.WE)
		free(cube->textures.WE);
	if (cube->textures.EA)
		free(cube->textures.EA);
	if (cube->map->width)
		free(cube->map->width);
	if (cube->map)
		free(cube->map);
	if (cube->player)
		free(cube->player);
	if (cube->img)
		free(cube->img);
	if (cube->raycast->dir)
		free(cube->raycast->dir);
	if (cube->raycast)
		free(cube->raycast);
	if (cube->key)
		free(cube->key);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	exit(0);
}
