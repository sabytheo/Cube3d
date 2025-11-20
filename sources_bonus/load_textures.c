/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:15:05 by egache            #+#    #+#             */
/*   Updated: 2025/11/20 16:28:09 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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
	cube->textures.DO_img.img = mlx_xpm_file_to_image(cube->mlx, textures->DO,
			&textures->DO_img.wh, &textures->DO_img.ht);
	cube->textures.FL_img.img = mlx_xpm_file_to_image(cube->mlx, textures->FL,
			&textures->FL_img.wh, &textures->FL_img.ht);
	cube->textures.CE_img.img = mlx_xpm_file_to_image(cube->mlx, textures->CE,
			&textures->CE_img.wh, &textures->CE_img.ht);
	cube->textures.SP_img.img = mlx_xpm_file_to_image(cube->mlx, textures->SP,
			&textures->SP_img.wh, &textures->SP_img.ht);
	if (!cube->textures.NO_img.img || !cube->textures.EA_img.img
		|| !cube->textures.SO_img.img || !cube->textures.WE_img.img
		|| !cube->textures.DO_img.img || !cube->textures.FL_img.img
		|| !cube->textures.CE_img.img || !cube->textures.SP_img.img)
		return (-1);
	return (0);
}

static int	get_data_addr_cardinal(t_textures *textures)
{
	textures->NO_img.addr = mlx_get_data_addr(textures->NO_img.img,
			&textures->NO_img.bpp, &textures->NO_img.sl, &textures->NO_img.en);
	textures->EA_img.addr = mlx_get_data_addr(textures->EA_img.img,
			&textures->EA_img.bpp, &textures->EA_img.sl, &textures->EA_img.en);
	textures->SO_img.addr = mlx_get_data_addr(textures->SO_img.img,
			&textures->SO_img.bpp, &textures->SO_img.sl, &textures->SO_img.en);
	textures->WE_img.addr = mlx_get_data_addr(textures->WE_img.img,
			&textures->WE_img.bpp, &textures->WE_img.sl, &textures->WE_img.en);
	if (!textures->NO_img.addr || !textures->EA_img.addr
		|| !textures->SO_img.addr || !textures->WE_img.addr)
		return (-1);
	return (0);
}

int	load_textures(t_game *cube, t_textures *textures)
{
	if (xpm_to_image(cube, textures) == 0)
	{
		if (get_data_addr_cardinal(textures) < 0)
			return (-1);
		textures->DO_img.addr = mlx_get_data_addr(textures->DO_img.img,
				&textures->DO_img.bpp, &textures->DO_img.sl,
				&textures->DO_img.en);
		textures->FL_img.addr = mlx_get_data_addr(textures->FL_img.img,
				&textures->FL_img.bpp, &textures->FL_img.sl,
				&textures->FL_img.en);
		textures->CE_img.addr = mlx_get_data_addr(textures->CE_img.img,
				&textures->CE_img.bpp, &textures->CE_img.sl,
				&textures->CE_img.en);
		textures->SP_img.addr = mlx_get_data_addr(textures->SP_img.img,
				&textures->SP_img.bpp, &textures->SP_img.sl,
				&textures->SP_img.en);
		if (!textures->DO_img.addr || !textures->FL_img.addr
			|| !textures->CE_img.addr || !textures->SP_img.addr)
			return (-1);
		return (0);
	}
	return (-1);
}
