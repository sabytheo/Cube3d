/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:15:05 by egache            #+#    #+#             */
/*   Updated: 2025/11/25 20:06:16 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static int	xpm_addr_animated(t_game *cube, t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		cube->textures.SO_img[i].img = mlx_xpm_file_to_image(cube->mlx,
				textures->SO[i], &textures->SO_img[i].wh,
				&textures->SO_img[i].ht);
		if (!cube->textures.SO_img[i].img)
		{
			ft_printf_fd(2, E_WRONG_PATH);
			return (-1);
		}
		textures->SO_img[i].addr = mlx_get_data_addr(textures->SO_img[i].img,
				&textures->SO_img[i].bpp, &textures->SO_img[i].sl,
				&textures->SO_img[i].en);
		if (!textures->SO_img[i].addr)
			return (-1);
		i++;
	}
	return (0);
}

static int	xpm_to_image(t_game *cube, t_textures *textures)
{
	if (xpm_addr_animated(cube, textures) < 0)
		return (-1);
	cube->textures.NO_img.img = mlx_xpm_file_to_image(cube->mlx, textures->NO,
			&textures->NO_img.wh, &textures->NO_img.ht);
	cube->textures.EA_img.img = mlx_xpm_file_to_image(cube->mlx, textures->EA,
			&textures->EA_img.wh, &textures->EA_img.ht);
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
		|| !cube->textures.WE_img.img || !cube->textures.DO_img.img
		|| !cube->textures.FL_img.img || !cube->textures.CE_img.img
		|| !cube->textures.SP_img.img)
	{
		ft_printf_fd(2, E_WRONG_PATH);
		return (-1);
	}
	return (0);
}

static int	get_data_addr_cardinal(t_textures *textures)
{
	textures->NO_img.addr = mlx_get_data_addr(textures->NO_img.img,
			&textures->NO_img.bpp, &textures->NO_img.sl, &textures->NO_img.en);
	textures->EA_img.addr = mlx_get_data_addr(textures->EA_img.img,
			&textures->EA_img.bpp, &textures->EA_img.sl, &textures->EA_img.en);
	textures->WE_img.addr = mlx_get_data_addr(textures->WE_img.img,
			&textures->WE_img.bpp, &textures->WE_img.sl, &textures->WE_img.en);
	if (!textures->NO_img.addr || !textures->EA_img.addr
		|| !textures->WE_img.addr)
		return (-1);
	return (0);
}

int	load_textures(t_game *cube, t_textures *textures)
{
	if (xpm_to_image(cube, textures) == 0)
	{
		cube->textures.current_frame = 0;
		gettimeofday(&cube->textures.last_frame_time, NULL);
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
