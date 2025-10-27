//
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fixed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: optimization                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by optim             #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by optim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <sys/time.h>

// Ajout dans cube.h dans la structure t_game :
// struct timeval last_frame;
// int frame_limit;

int init(t_game *cube)
{
	ft_bzero(cube, sizeof(t_game));
	cube->map = (t_map *)ft_calloc(1, sizeof(t_map));
	cube->player = (t_player *)ft_calloc(1, sizeof(t_player));
	cube->img = (t_img *)ft_calloc(1, sizeof(t_img));
	cube->raycast = (t_raycast *)ft_calloc(1, sizeof(t_raycast));
	cube->raycast->dir = (t_vector *)ft_calloc(1, sizeof(t_vector));
	cube->key = (t_key*)ft_calloc(1,sizeof(t_key));

	cube->fps_counter = init_fps_counter();
	if (!cube->map || !cube->player || !cube->img || !cube->raycast ||
		!cube->raycast->dir || !cube->key)
	{
		ft_printf_fd(2, "Error:\n Failed to allocate memory\n");
		return (-1);
	}

	// Initialiser le timer
	gettimeofday(&cube->last_frame, NULL);
	cube->frame_limit = 16666; // ~60 FPS (16.666ms par frame)

	return (0);
}

int	load_textures(t_game *cube)
{
	cube->textures.CE_img.img_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->textures.CE, &cube->textures.CE_img.width,
			&cube->textures.CE_img.height);
	if (!cube->textures.CE_img.img_ptr)
		return (-1);
	cube->textures.CE_img.addr = mlx_get_data_addr(cube->textures.CE_img.img_ptr,
			&cube->textures.CE_img.bits_per_pixel,
			&cube->textures.CE_img.size_line, &cube->textures.CE_img.endian);
	cube->textures.FL_img.img_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->textures.FL, &cube->textures.FL_img.width,
			&cube->textures.FL_img.height);
	if (!cube->textures.FL_img.img_ptr)
		return (-1);
	cube->textures.FL_img.addr = mlx_get_data_addr(cube->textures.FL_img.img_ptr,
			&cube->textures.FL_img.bits_per_pixel,
			&cube->textures.FL_img.size_line, &cube->textures.FL_img.endian);
	cube->textures.NO_img.img_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->textures.NO, &cube->textures.NO_img.width,
			&cube->textures.NO_img.height);
	if (!cube->textures.NO_img.img_ptr)
		return (-1);
	cube->textures.NO_img.addr = mlx_get_data_addr(cube->textures.NO_img.img_ptr,
			&cube->textures.NO_img.bits_per_pixel,
			&cube->textures.NO_img.size_line, &cube->textures.NO_img.endian);
	cube->textures.DO_img.img_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->textures.DO, &cube->textures.DO_img.width,
			&cube->textures.DO_img.height);
	if (!cube->textures.DO_img.img_ptr)
		return (-1);
	cube->textures.DO_img.addr = mlx_get_data_addr(cube->textures.DO_img.img_ptr,
			&cube->textures.DO_img.bits_per_pixel,
			&cube->textures.DO_img.size_line, &cube->textures.DO_img.endian);
	cube->textures.SO_img.img_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->textures.SO, &cube->textures.SO_img.width,
			&cube->textures.SO_img.height);
	if (!cube->textures.SO_img.img_ptr)
		return (-1);
	cube->textures.SO_img.addr = mlx_get_data_addr(cube->textures.SO_img.img_ptr,
			&cube->textures.SO_img.bits_per_pixel,
			&cube->textures.SO_img.size_line, &cube->textures.SO_img.endian);
	cube->textures.EA_img.img_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->textures.EA, &cube->textures.EA_img.width,
			&cube->textures.EA_img.height);
	if (!cube->textures.EA_img.img_ptr)
		return (-1);
	cube->textures.EA_img.addr = mlx_get_data_addr(cube->textures.EA_img.img_ptr,
			&cube->textures.EA_img.bits_per_pixel,
			&cube->textures.EA_img.size_line, &cube->textures.EA_img.endian);

	cube->textures.WE_img.img_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->textures.WE, &cube->textures.WE_img.width,
			&cube->textures.WE_img.height);
	if (!cube->textures.WE_img.img_ptr)
		return (-1);
	cube->textures.WE_img.addr = mlx_get_data_addr(cube->textures.WE_img.img_ptr,
			&cube->textures.WE_img.bits_per_pixel,
			&cube->textures.WE_img.size_line, &cube->textures.WE_img.endian);
	return (0);
}

int main(int argc, char **argv)
{
	t_game cube;

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
	cube.img->img_ptr = mlx_new_image(cube.mlx, WIDTH, HEIGHT);
	cube.img->addr = mlx_get_data_addr(cube.img->img_ptr,
		&cube.img->bits_per_pixel, &cube.img->size_line, &cube.img->endian);

	// Premier rendu
	render(&cube);

	// Hooks
	mlx_hook(cube.windows, 2, 1L << 0, press_key, &cube);
	mlx_hook(cube.windows, 3, 1L << 1, release_key, &cube);
	mlx_loop_hook(cube.mlx, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, 0, free_exit, &cube);

	mlx_loop(cube.mlx);
	return (0);
}
