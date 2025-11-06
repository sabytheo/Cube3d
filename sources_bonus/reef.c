/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reef.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:37:43 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:25:21 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

static void destroy_image(t_game *cube)
{
	if (cube->textures.EA_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.EA_img.img);
	if (cube->img->img)
		mlx_destroy_image(cube->mlx, cube->img->img);
	if (cube->minimap_img->img)
		mlx_destroy_image(cube->mlx, cube->minimap_img->img);
	if (cube->textures.NO_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.NO_img.img);
	if (cube->textures.SO_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.SO_img.img);
	if (cube->textures.WE_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.WE_img.img);
	if (cube->textures.DO_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.DO_img.img);
	if (cube->textures.FL_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.FL_img.img);
	if (cube->textures.CE_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.CE_img.img);
	if (cube->textures.SP_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.SP_img.img);
	return;
}
static void clean_textures(t_game *cube)
{
	if (cube->textures.NO)
		free(cube->textures.NO);
	if (cube->textures.SO)
		free(cube->textures.SO);
	if (cube->textures.WE)
		free(cube->textures.WE);
	if (cube->textures.EA)
		free(cube->textures.EA);
	if (cube->textures.DO)
		free(cube->textures.DO);
	if (cube->textures.FL)
		free(cube->textures.FL);
	if (cube->textures.SP)
		free(cube->textures.SP);
	if (cube->textures.CE)
		free(cube->textures.CE);
	return;
}

static void clean_struct(t_game *cube)
{
	if (cube->map)
		free(cube->map);
	// if (cube->player)
	// 	free(cube->player);
	if (cube->minimap_img)
		free(cube->minimap_img);
	if (cube->minimap_values)
		free(cube->minimap_values);
	if (cube->img)
		free(cube->img);
	if (cube->raycast->dir)
		free(cube->raycast->dir);
	if (cube->raycast)
		free(cube->raycast);
	if (cube->key)
		free(cube->key);
	return;
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
