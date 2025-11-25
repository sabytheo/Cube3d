/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reef.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:37:43 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/25 16:34:33 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	clean_animation(t_game *cube)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (cube->textures.SO_img[i].img)
			mlx_destroy_image(cube->mlx, cube->textures.SO_img[i].img);
		if (cube->textures.SO[i])
			free(cube->textures.SO[i]);
		i++;
	}
}

static void	destroy_image(t_game *cube)
{
	if (cube->textures.EA_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.EA_img.img);
	if (cube->img->img)
		mlx_destroy_image(cube->mlx, cube->img->img);
	if (cube->minimap_img->img)
		mlx_destroy_image(cube->mlx, cube->minimap_img->img);
	if (cube->textures.NO_img.img)
		mlx_destroy_image(cube->mlx, cube->textures.NO_img.img);
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
	return ;
}

static void	clean_textures(t_game *cube)
{
	if (cube->textures.NO)
		free(cube->textures.NO);
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
	return ;
}

static void	clean_struct(t_game *cube)
{
	if (cube->minimap_img)
		free(cube->minimap_img);
	if (cube->img)
		free(cube->img);
	if (cube->fps_counter)
		free(cube->fps_counter);
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
	clean_struct(cube);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	exit(0);
}
