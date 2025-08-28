/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:46:21 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/28 17:23:19 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <string.h>

int	define_control(int keypress, t_game *cube)
{
	if (keypress == ESCAPE)
		free_exit(cube, EXIT_SUCCESS);
	return (1);
}

int	init(t_game *cube)
{
	ft_bzero(cube, sizeof(t_game));
	cube->map = (t_map *)ft_calloc(1,sizeof(t_map));
	cube->textures = (t_textures *)ft_calloc(1,sizeof(t_textures));
	cube->textures->wall = (char**)ft_calloc(1, sizeof(char*) * 5);
	cube->textures->fc = (char**)ft_calloc(1, sizeof(char*) * 3);
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
	if (parse_map(&cube, argv))
		free_exit(&cube,EXIT_FAILURE);
	cube.mlx = mlx_init();
	if (!cube.mlx)
		return (0);
	cube.windows = mlx_new_window(cube.mlx, 1280, 720, "CUBE3D");
	mlx_key_hook(cube.windows, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, BUTTON_PRESS_MASK, free_exit, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
