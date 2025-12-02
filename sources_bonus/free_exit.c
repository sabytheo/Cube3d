/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:37:43 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/02 15:52:26 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	clean_animation(t_game *cube)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (cube->textures.so_img[i].img)
			mlx_destroy_image(cube->mlx, cube->textures.so_img[i].img);
		if (cube->textures.so[i])
			free(cube->textures.so[i]);
		i++;
	}
}

static void	destroy_image(t_game *cube)
{
	if (cube->textures.ea_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.ea_img.img);
	if (cube->img->img)
		mlx_destroy_image(cube->mlx, cube->img->img);
	if (cube->minimap_img->img)
		mlx_destroy_image(cube->mlx, cube->minimap_img->img);
	if (cube->textures.no_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.no_img.img);
	if (cube->textures.we_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.we_img.img);
	if (cube->textures.od_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.od_img.img);
	if (cube->textures.fl_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.fl_img.img);
	if (cube->textures.ce_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.ce_img.img);
	if (cube->textures.cd_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.cd_img.img);
	return ;
}

static void	clean_textures(t_game *cube)
{
	if (cube->textures.no)
		free(cube->textures.no);
	if (cube->textures.we)
		free(cube->textures.we);
	if (cube->textures.ea)
		free(cube->textures.ea);
	if (cube->textures.od)
		free(cube->textures.od);
	if (cube->textures.fl)
		free(cube->textures.fl);
	if (cube->textures.cd)
		free(cube->textures.cd);
	if (cube->textures.ce)
		free(cube->textures.ce);
	return ;
}

static void	clean_struct(t_game *cube)
{
	if (cube->minimap_img)
		free(cube->minimap_img);
	if (cube->img)
		free(cube->img);
	return ;
}

int	free_exit(t_game *cube)
{
	if (cube->windows)
		mlx_destroy_window(cube->mlx, cube->windows);
	clean_animation(cube);
	destroy_image(cube);
	clean_textures(cube);
	if (cube->map.grid)
		free_tab(cube->map.grid);
	if (cube->map.final_grid)
		free_tab(cube->map.final_grid);
	if (cube->map.width)
		free(cube->map.width);
	pthread_mutex_destroy(&cube->running_lock);
	clean_struct(cube);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	exit(0);
}
