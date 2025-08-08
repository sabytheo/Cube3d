/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:46:21 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/08 15:49:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	free_exit(t_gamestruct *cube)
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

int	define_control(int keypress, t_gamestruct *cube)
{
	if (keypress == ESCAPE)
		free_exit(cube);
	return (1);
}

int main(int argc, char **argv)
{
	t_gamestruct	cube;

	if (argc != 2)
	{
		write(2, "Number of arguments invalid\n", 28);
		exit(0);
	}
	ft_memset(&cube, 0, sizeof(t_gamestruct));
	cube.mlx = mlx_init();
	if (!cube.mlx)
		return (0);
	cube.windows = mlx_new_window(cube.mlx, 1280, 720 , "CUBE3D");
	parse_map(&cube,argv);
	mlx_key_hook(cube.windows, define_control, &cube);
	mlx_hook(cube.windows, ON_DESTROY, BUTTON_PRESS_MASK, free_exit, &cube);
	mlx_loop(cube.mlx);
	return (1);
}
