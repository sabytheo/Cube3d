/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:21:32 by egache            #+#    #+#             */
/*   Updated: 2025/11/19 16:22:21 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	xpm_to_image(t_game *cube, t_textures *textures)
{
	cube->textures.NO_img.img = mlx_xpm_file_to_image(cube->mlx, textures->NO,
			&textures->NO_img.wh, &textures->NO_img.ht);
	cube->textures.EA_img.img = mlx_xpm_file_to_image(cube->mlx, textures->EA,
			&textures->EA_img.wh, &textures->EA_img.ht);
	cube->textures.SO_img.img = mlx_xpm_file_to_image(cube->mlx, textures->SO,
			&textures->SO_img.wh, &textures->SO_img.ht);
	cube->textures.WE_img.img = mlx_xpm_file_to_image(cube->mlx, textures->WE,
			&textures->WE_img.wh, &textures->WE_img.ht);
	if (!cube->textures.EA_img.img)
		return (-1);
	return (0);
}

int	load_textures(t_game *cube)
{
	if (xpm_to_image(cube, &cube->textures) == 0)
	{
		cube->textures.NO_img.addr = mlx_get_data_addr(cube->textures.NO_img.img,
				&cube->textures.NO_img.bpp, &cube->textures.NO_img.sl,
				&cube->textures.NO_img.en);
		cube->textures.EA_img.addr = mlx_get_data_addr(cube->textures.EA_img.img,
				&cube->textures.EA_img.bpp, &cube->textures.EA_img.sl,
				&cube->textures.EA_img.en);
		cube->textures.SO_img.addr = mlx_get_data_addr(cube->textures.SO_img.img,
				&cube->textures.SO_img.bpp, &cube->textures.SO_img.sl,
				&cube->textures.SO_img.en);
		cube->textures.WE_img.addr = mlx_get_data_addr(cube->textures.WE_img.img,
				&cube->textures.WE_img.bpp, &cube->textures.WE_img.sl,
				&cube->textures.WE_img.en);
		return (0);
	}
	return (-1);
}
