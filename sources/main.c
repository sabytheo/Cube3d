/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:46:14 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/11 15:53:48 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	if (!cube->img)
		return (-1);
	init_values(cube);
	return (0);
}

void	render(t_game *cube)
{
	raycast(cube, &cube->raycast);
	mlx_put_image_to_window(cube->mlx, cube->windows, cube->img->img, 0, 0);
}

static void	init_window_and_img(t_game *cube)
{
	cube->windows = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "CUB3D");
	cube->img->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->windows || !cube->img->img)
		free_exit(cube);
	cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp,
			&cube->img->sl, &cube->img->en);
	if (!cube->img->addr)
		free_exit(cube);
}

int	main(int argc, char **argv)
{
	t_game	cube;

	if (argc != 2)
	{
		write(2, "Error\nNumber of arguments invalid\n", 28);
		exit(1);
	}
	if (init(&cube))
		exit(1);
	if (parse_map(&cube, argv) < 0)
		free_exit(&cube);
	cube.mlx = mlx_init();
	if (!cube.mlx)
		free_exit(&cube);
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
