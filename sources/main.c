/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:46:14 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:45:02 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <sys/time.h>

int	init(t_game *cube)
{
	ft_bzero(cube, sizeof(t_game));
	cube->img = (t_img *)ft_calloc(1, sizeof(t_img));
	cube->player.speed = 0.25;
	//cube->fps_counter = init_fps_counter();
	if (!cube->img)
	{
		ft_printf_fd(2, "Error:\n Failed to allocate memory\n");
		return (-1);
	}
	// Initialiser le timer
	// gettimeofday(&cube->last_frame, NULL);
	// cube->frame_limit = 16666; // ~60 FPS (16.666ms par frame)
	return (0);
}
int	xpm_to_image(t_game *cube, t_texture *textures)
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

int	main(int argc, char **argv)
{
	t_game	cube;

	if (argc != 2)
	{
		write(2, "Number of arguments invalid\n", 28);
		exit(0);
	}
	if (init(&cube))
		exit(1);
	if (parse_map(&cube, argv))
		free_exit(&cube);
	cube.mlx = mlx_init();
	if (!cube.mlx)
		return (0);
	if (load_textures(&cube) < 0)
		free_exit(&cube);
	cube.windows = mlx_new_window(cube.mlx, WIDTH, HEIGHT, "CUB3D");
	cube.img->img = mlx_new_image(cube.mlx, WIDTH, HEIGHT);
	cube.img->addr = mlx_get_data_addr(cube.img->img, &cube.img->bpp,
			&cube.img->sl, &cube.img->en);
	render(&cube);
	mlx_hook(cube.windows, 2, 1L << 0, press_key, &cube);
	mlx_hook(cube.windows, 3, 1L << 1, release_key, &cube);
	mlx_loop_hook(cube.mlx, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, 0, free_exit, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
