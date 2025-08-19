/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:46:21 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/19 19:15:44 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	free_exit(t_game *cube)
{
	if (cube->windows)
		mlx_destroy_window(cube->mlx, cube->windows);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	exit(0);
}

int	define_control(int keypress, t_game *cube)
{
	if (keypress == ESCAPE)
		free_exit(cube);
	return (1);
}

int init(t_game *cube)
{
	ft_bzero(cube, sizeof(t_game));
    cube->map = (t_map *)malloc(sizeof(t_map));
    // if (!cube->map)
    // {
    //     ft_printf_fd(2, "Error:\n Failed to allocate cube->map\n");
    //     return (-1);
    // }
    cube->map->height = 0;
    cube->map->grid = NULL;
	return (0);

}
int	main(int argc, char **argv)
{
	t_game	cube;

	if (argc != 2)
	{
		write(2, "Number of arguments invalid\n", 28);
		exit(0);
	}
	init(&cube);
	// ft_memset(&cube.map, 0, sizeof(t_map));
	// ft_memset(&cube.player, 0, sizeof(t_player));
	if (parse_map(&cube, argv))
		return (-1);
	cube.mlx = mlx_init();
	if (!cube.mlx)
		return (0);
	cube.windows = mlx_new_window(cube.mlx, 1280, 720, "CUBE3D");
	// cube.img_ptr = mlx_new_image(cube.mlx, 1280, 720);
	// cube.img_data = mlx_get_data_addr(cube.img_ptr, &cube.bits, &cube.size_line,
	// 		&cube.endian);
	mlx_key_hook(cube.windows, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, BUTTON_PRESS_MASK, free_exit, &cube);
	mlx_loop(cube.mlx);
	return (1);
}
