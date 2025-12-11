/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:21:32 by egache            #+#    #+#             */
/*   Updated: 2025/12/11 15:30:46 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	xpm_to_image(t_game *cube, t_textures *textures)
{
	cube->textures.no_img.img = mlx_xpm_file_to_image(cube->mlx, textures->no,
			&textures->no_img.wh, &textures->no_img.ht);
	cube->textures.ea_img.img = mlx_xpm_file_to_image(cube->mlx, textures->ea,
			&textures->ea_img.wh, &textures->ea_img.ht);
	cube->textures.so_img.img = mlx_xpm_file_to_image(cube->mlx, textures->so,
			&textures->so_img.wh, &textures->so_img.ht);
	cube->textures.we_img.img = mlx_xpm_file_to_image(cube->mlx, textures->we,
			&textures->we_img.wh, &textures->we_img.ht);
	if (!cube->textures.no_img.img || !cube->textures.ea_img.img
		|| !cube->textures.so_img.img || !cube->textures.we_img.img)
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
		textures->no_img.addr = mlx_get_data_addr(textures->no_img.img,
				&textures->no_img.bpp, &textures->no_img.sl,
				&textures->no_img.en);
		textures->ea_img.addr = mlx_get_data_addr(textures->ea_img.img,
				&textures->ea_img.bpp, &textures->ea_img.sl,
				&textures->ea_img.en);
		textures->so_img.addr = mlx_get_data_addr(textures->so_img.img,
				&textures->so_img.bpp, &textures->so_img.sl,
				&textures->so_img.en);
		textures->we_img.addr = mlx_get_data_addr(textures->we_img.img,
				&textures->we_img.bpp, &textures->we_img.sl,
				&textures->we_img.en);
		if (!textures->no_img.addr || !textures->so_img.addr
			|| !textures->ea_img.addr || !textures->we_img.addr)
			return (-1);
		return (0);
	}
	return (-1);
}
