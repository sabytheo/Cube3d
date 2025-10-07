/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:46:21 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/07 14:28:21 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	define_control(int keypress, t_game *cube)
{
	if (keypress == ESCAPE)
		free_exit(cube);
	return (1);
}

int	init(t_game *cube)
{
	ft_bzero(cube, sizeof(t_game));
	cube->map = (t_map *)ft_calloc(1, sizeof(t_map));
	cube->player = (t_player *)ft_calloc(1, sizeof(t_player));
	cube->img = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!cube->map)
	{
		ft_printf_fd(2, "Error:\n Failed to allocate cube->map\n");
		return (-1);
	}
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
	if (parse_map(&cube, argv))
		free_exit(&cube);
	cube.mlx = mlx_init();
	if (!cube.mlx)
		return (0);
	cube.windows = mlx_new_window(cube.mlx, WIDTH, HEIGHT, "CUBE3D");
	cube.img->img_ptr = mlx_new_image(cube.mlx, WIDTH, HEIGHT);
	cube.img->addr = mlx_get_data_addr(cube.img->img_ptr,&cube.img->bits_per_pixel,&cube.img->size_line,&cube.img->endian);
	render(&cube);
	mlx_key_hook(cube.windows, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, BUTTON_PRESS_MASK, free_exit, &cube);
	mlx_loop(cube.mlx);
	return (1);
}
