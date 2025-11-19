/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/19 16:19:29 by egache           ###   ########.fr       */
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
	cube->player.speed = 1;
	cube->player.rotation_speed = 1;
	cube->last_mouse_pos_x = WIDTH / 2;
	cube->delta_time = 0.016;
	cube->fps_counter = init_fps_counter();
	gettimeofday(&cube->last_frame, NULL);
	if (!cube->img || !cube->minimap_img)
	{
		ft_printf_fd(2, "Error:\n Failed to allocate memory\n");
		return (-1);
	}
	// // Initialiser le timer
	// cube->frame_limit = 16666; // ~60 FPS (16.666ms par frame)
	return (0);
}

void	render(t_game *cube)
{
	launch_threads(cube);
	render_mapmap(cube->minimap_img, cube);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->minimap_img->img, 0,
		0);
	update_fps_counter(cube);
	draw_debug_info_cardinal(cube);
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
	cube.img->img = mlx_new_image(cube.mlx, WIDTH, WIDTH);
	cube.img->addr = mlx_get_data_addr(cube.img->img, &cube.img->bpp,
			&cube.img->sl, &cube.img->en);
	cube.minimap_img->img = mlx_new_image(cube.mlx, WIDTH * 0.2, WIDTH * 0.2);
	cube.minimap_img->addr = mlx_get_data_addr(cube.minimap_img->img,
			&cube.minimap_img->bpp, &cube.minimap_img->sl,
			&cube.minimap_img->en);
	init_height_dplan(&cube, &cube.raycast);
	render(&cube);
	mlx_hook(cube.windows, 2, 1L << 0, press_key, &cube);
	mlx_hook(cube.windows, 3, 1L << 1, release_key, &cube);
	// mlx_hook(cube.windows, 6, 1L << 6, mouse_move, &cube);
	mlx_loop_hook(cube.mlx, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, 0, free_exit, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
