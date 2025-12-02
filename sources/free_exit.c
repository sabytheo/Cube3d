/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:37:43 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/02 15:44:13 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	destroy_image(t_game *cube)
{
	if (cube->textures.ea_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.ea_img.img);
	if (cube->img->img)
		mlx_destroy_image(cube->mlx, cube->img->img);
	if (cube->textures.no_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.no_img.img);
	if (cube->textures.so_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.so_img.img);
	if (cube->textures.we_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.we_img.img);
	return ;
}

static void	clean_textures(t_game *cube)
{
	if (cube->textures.no)
		free(cube->textures.no);
	if (cube->textures.so)
		free(cube->textures.so);
	if (cube->textures.we)
		free(cube->textures.we);
	if (cube->textures.ea)
		free(cube->textures.ea);
	return ;
}

static void	clean_struct(t_game *cube)
{
	if (cube->img)
		free(cube->img);
	return ;
}

int	free_exit(t_game *cube)
{
	if (cube->windows)
		mlx_destroy_window(cube->mlx, cube->windows);
	destroy_image(cube);
	clean_textures(cube);
	if (cube->map.grid)
		free_tab(cube->map.grid);
	if (cube->map.final_grid)
		free_tab(cube->map.final_grid);
	if (cube->map.width)
		free(cube->map.width);
	clean_struct(cube);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	exit(0);
}
