/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:15:05 by egache            #+#    #+#             */
/*   Updated: 2025/12/11 15:52:57 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static int	xpm_addr_animated(t_game *cube, t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		cube->textures.so_img[i].img = mlx_xpm_file_to_image(cube->mlx,
				textures->so[i], &textures->so_img[i].wh,
				&textures->so_img[i].ht);
		if (!cube->textures.so_img[i].img)
		{
			ft_printf_fd(2, "Error\nUnexpected texture path\n");
			return (-1);
		}
		textures->so_img[i].addr = mlx_get_data_addr(textures->so_img[i].img,
				&textures->so_img[i].bpp, &textures->so_img[i].sl,
				&textures->so_img[i].en);
		if (!textures->so_img[i].addr)
			return (-1);
		i++;
	}
	return (0);
}

static int	xpm_to_image(t_game *cube, t_textures *textures)
{
	if (xpm_addr_animated(cube, textures) < 0)
		return (-1);
	cube->textures.no_img.img = mlx_xpm_file_to_image(cube->mlx, textures->no,
			&textures->no_img.wh, &textures->no_img.ht);
	cube->textures.ea_img.img = mlx_xpm_file_to_image(cube->mlx, textures->ea,
			&textures->ea_img.wh, &textures->ea_img.ht);
	cube->textures.we_img.img = mlx_xpm_file_to_image(cube->mlx, textures->we,
			&textures->we_img.wh, &textures->we_img.ht);
	cube->textures.od_img.img = mlx_xpm_file_to_image(cube->mlx, textures->od,
			&textures->od_img.wh, &textures->od_img.ht);
	cube->textures.fl_img.img = mlx_xpm_file_to_image(cube->mlx, textures->fl,
			&textures->fl_img.wh, &textures->fl_img.ht);
	cube->textures.ce_img.img = mlx_xpm_file_to_image(cube->mlx, textures->ce,
			&textures->ce_img.wh, &textures->ce_img.ht);
	cube->textures.cd_img.img = mlx_xpm_file_to_image(cube->mlx, textures->cd,
			&textures->cd_img.wh, &textures->cd_img.ht);
	if (!cube->textures.no_img.img || !cube->textures.ea_img.img
		|| !cube->textures.we_img.img || !cube->textures.od_img.img
		|| !cube->textures.fl_img.img || !cube->textures.ce_img.img
		|| !cube->textures.cd_img.img)
	{
		ft_printf_fd(2, E_WRONG_PATH);
		return (-1);
	}
	return (0);
}

static int	get_data_addr_cardinal(t_textures *textures)
{
	textures->no_img.addr = mlx_get_data_addr(textures->no_img.img,
			&textures->no_img.bpp, &textures->no_img.sl, &textures->no_img.en);
	textures->ea_img.addr = mlx_get_data_addr(textures->ea_img.img,
			&textures->ea_img.bpp, &textures->ea_img.sl, &textures->ea_img.en);
	textures->we_img.addr = mlx_get_data_addr(textures->we_img.img,
			&textures->we_img.bpp, &textures->we_img.sl, &textures->we_img.en);
	if (!textures->no_img.addr || !textures->ea_img.addr
		|| !textures->we_img.addr)
	{
		ft_printf_fd(2, E_BAD_DATA_ADDR);
		return (-1);
	}
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
		textures->od_img.addr = mlx_get_data_addr(textures->od_img.img,
				&textures->od_img.bpp, &textures->od_img.sl,
				&textures->od_img.en);
		textures->fl_img.addr = mlx_get_data_addr(textures->fl_img.img,
				&textures->fl_img.bpp, &textures->fl_img.sl,
				&textures->fl_img.en);
		textures->ce_img.addr = mlx_get_data_addr(textures->ce_img.img,
				&textures->ce_img.bpp, &textures->ce_img.sl,
				&textures->ce_img.en);
		textures->cd_img.addr = mlx_get_data_addr(textures->cd_img.img,
				&textures->cd_img.bpp, &textures->cd_img.sl,
				&textures->cd_img.en);
		if (!textures->od_img.addr || !textures->fl_img.addr
			|| !textures->ce_img.addr || !textures->cd_img.addr)
			return (-1);
		return (0);
	}
	return (-1);
}
