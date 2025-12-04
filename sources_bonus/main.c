/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/04 14:06:17 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static int	check_game_values(void)
{
	if (WIDTH < 960 || HEIGHT < 540 || WIDTH > 1920 || HEIGHT > 1080)
	{
		ft_printf_fd(2, E_WRONG_INIT);
		return (-1);
	}
	if ((WIDTH * 9) != (HEIGHT * 16))
	{
		ft_printf_fd(2, E_WRONG_INIT);
		return (-1);
	}
	if (XBOX != 0.2)
	{
		ft_printf_fd(2, E_WRONG_INIT);
		return (-1);
	}
	return (0);
}

static int	init(t_game *cube)
{
	ft_bzero(cube, sizeof(t_game));
	if (check_game_values() < 0)
		return (-1);
	cube->img = (t_img *)ft_calloc(1, sizeof(t_img));
	cube->minimap_img = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!cube->img || !cube->minimap_img)
		return (-1);
	init_values(cube);
	return (0);
}

void	render(t_game *cube)
{
	t_cube_thread	**cube_thread;

	cube_thread = malloc(cube->nb_cores * sizeof(t_cube_thread));
	if (!cube_thread)
		free_exit(cube);
	if (launch_threads(cube, cube_thread) < 0)
	{
		free_threads_tab(cube, cube_thread);
		free_exit(cube);
	}
	render_minimap(cube->minimap_img, cube);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->minimap_img->img, 0,
		0);
}

static void	init_window_and_img(t_game *cube)
{
	cube->windows = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "CUB3D");
	cube->img->img = mlx_new_image(cube->mlx, WIDTH, WIDTH);
	cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp,
			&cube->img->sl, &cube->img->en);
	cube->minimap_img->img = mlx_new_image(cube->mlx, WIDTH * 0.2, WIDTH * 0.2);
	cube->minimap_img->addr = mlx_get_data_addr(cube->minimap_img->img,
			&cube->minimap_img->bpp, &cube->minimap_img->sl,
			&cube->minimap_img->en);
}

int	main(int argc, char **argv)
{
	t_game	cube;

	if (argc != 2)
	{
		write(2, "Error :\nNumber of arguments invalid\n", 28);
		exit(0);
	}
	if (init(&cube))
		exit(1);
	if (parse_map(&cube, argv))
		free_exit(&cube);
	cube.mlx = mlx_init();
	if (!cube.mlx)
		return (0);
	if (load_textures(&cube, &cube.textures) < 0)
		free_exit(&cube);
	init_window_and_img(&cube);
	render(&cube);
	mlx_hook(cube.windows, 2, 1L << 0, press_key, &cube);
	mlx_hook(cube.windows, 3, 1L << 1, release_key, &cube);
	mlx_loop_hook(cube.mlx, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, 0, free_exit, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
