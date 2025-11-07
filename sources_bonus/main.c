/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/07 16:34:01 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include <sys/time.h>

int	init(t_game *cube)
{
	ft_bzero(cube, sizeof(t_game));
	cube->nb_cores = sysconf(_SC_NPROCESSORS_ONLN);
	cube->img = (t_img *)ft_calloc(1, sizeof(t_img));
	cube->minimap_img = (t_img *)ft_calloc(1, sizeof(t_img));
	// cube->hit_info = (t_hit_info*)ft_calloc(1,sizeof(t_hit_info));
	cube->player.speed = 0.1;
	cube->fps_counter = init_fps_counter();
	if (!cube->img || !cube->minimap_img)
	{
		ft_printf_fd(2, "Error:\n Failed to allocate memory\n");
		return (-1);
	}
	// // Initialiser le timer
	gettimeofday(&cube->last_frame, NULL);
	cube->frame_limit = 16666; // ~60 FPS (16.666ms par frame)
	return (0);
}

int	xpm_to_image(t_game *cube, t_textures *textures)
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

static int get_data_addr_cardinal(t_textures *textures)
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
		if (!textures->NO_img.addr || !textures->EA_img.addr
		|| !textures->SO_img.addr || !textures->WE_img.addr )
			return (-1);
		return (0);
}
int	load_textures(t_game *cube)
{
	if (xpm_to_image(cube, &cube->textures) == 0)
	{

		if (get_data_addr_cardinal(&cube->textures) < 0)
			return (-1);
		cube->textures.DO_img.addr = mlx_get_data_addr(cube->textures.DO_img.img,
				&cube->textures.DO_img.bpp, &cube->textures.DO_img.sl,
				&cube->textures.DO_img.en);
		cube->textures.FL_img.addr = mlx_get_data_addr(cube->textures.FL_img.img,
				&cube->textures.FL_img.bpp, &cube->textures.FL_img.sl,
				&cube->textures.FL_img.en);
		cube->textures.CE_img.addr = mlx_get_data_addr(cube->textures.CE_img.img,
				&cube->textures.CE_img.bpp, &cube->textures.CE_img.sl,
				&cube->textures.CE_img.en);
		cube->textures.SP_img.addr = mlx_get_data_addr(cube->textures.SP_img.img,
				&cube->textures.SP_img.bpp, &cube->textures.SP_img.sl,
				&cube->textures.SP_img.en);
		if (!cube->textures.DO_img.addr || !cube->textures.FL_img.addr
		|| !cube->textures.CE_img.addr || !cube->textures.SP_img.addr)
			return (-1);
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
	cube.thread_img = (t_img **)ft_calloc(cube.nb_cores, sizeof(t_img *));
	int i = 0;
	while (i < cube.nb_cores)
	{
		cube.thread_img[i] = (t_img *)ft_calloc(1, sizeof(t_img));
		cube.thread_img[i]->img = mlx_new_image(cube.mlx, WIDTH - (WIDTH / cube.nb_cores), HEIGHT);
		cube.thread_img[i]->addr = mlx_get_data_addr(cube.thread_img[i]->img,
			&cube.thread_img[i]->bpp, &cube.thread_img[i]->sl, &cube.thread_img[i]->en);
	}
	cube.img->img = mlx_new_image(cube.mlx, WIDTH, WIDTH);
	cube.img->addr = mlx_get_data_addr(cube.img->img,
			&cube.img->bpp, &cube.img->sl, &cube.img->en);
	cube.minimap_img->img = mlx_new_image(cube.mlx, WIDTH * 0.2, WIDTH * 0.2);
	cube.minimap_img->addr = mlx_get_data_addr(cube.minimap_img->img,
			&cube.minimap_img->bpp, &cube.minimap_img->sl, &cube.minimap_img->en);
	init_height_dplan(&cube, &cube.raycast);
	render(&cube);
	mlx_hook(cube.windows, 2, 1L << 0, press_key, &cube);
	mlx_hook(cube.windows, 3, 1L << 1, release_key, &cube);
	mlx_loop_hook(cube.mlx, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, 0, free_exit, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
