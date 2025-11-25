/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:21:32 by egache            #+#    #+#             */
/*   Updated: 2025/11/25 19:25:53 by tsaby            ###   ########.fr       */
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
	if (!cube->textures.NO_img.img || !cube->textures.EA_img.img
		|| !cube->textures.SO_img.img || !cube->textures.WE_img.img)
	{
		ft_printf_fd(2, E_WRONG_PATH);
		return (-1);
	}
	return (0);
}

int	load_textures(t_game *cube, t_textures *textures)
{
	if (xpm_to_image(cube, textures) == 0)
	{
		textures->NO_img.addr = mlx_get_data_addr(textures->NO_img.img,
				&textures->NO_img.bpp, &textures->NO_img.sl,
				&textures->NO_img.en);
		textures->EA_img.addr = mlx_get_data_addr(textures->EA_img.img,
				&textures->EA_img.bpp, &textures->EA_img.sl,
				&textures->EA_img.en);
		textures->SO_img.addr = mlx_get_data_addr(textures->SO_img.img,
				&textures->SO_img.bpp, &textures->SO_img.sl,
				&textures->SO_img.en);
		textures->WE_img.addr = mlx_get_data_addr(textures->WE_img.img,
				&textures->WE_img.bpp, &textures->WE_img.sl,
				&textures->WE_img.en);
		if (!textures->NO_img.addr || !textures->SO_img.addr
			|| !textures->EA_img.addr || !textures->WE_img.addr)
			return (-1);
		return (0);
	}
	return (-1);
}
