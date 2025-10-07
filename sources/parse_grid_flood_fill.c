/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grod_flood_fill.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:49:13 by egache            #+#    #+#             */
/*   Updated: 2025/10/07 12:49:27 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void flood_fill(int i, int j, t_game *cube)
{
	if (i < 0 || i >= cube->map->total_height || j < 0 || j >= cube->map->width[i])
		return;
	while (cube->map->grid[i][j] == ' ' && cube->map->grid[i][j] != '\n')
		j++;
	if (is_a_player(cube->map->grid[i][j]))
		cube->map->grid[i][j] = '3';
	else if (cube->map->grid[i][j] == 'D')
		cube->map->grid[i][j] = '2';
	else if (cube->map->grid[i][j] == '0')
		cube->map->grid[i][j] = 'F';
	else
		return ;
	flood_fill(i + 1, j, cube);
	flood_fill(i - 1, j, cube);
	flood_fill(i, j + 1, cube);
	flood_fill(i, j - 1, cube);
}

int vlood_vill(int i, int j, t_game *cube)
{
	if (i < 0 || i >= cube->map->grid_height || !cube->map->final_grid[i])
		return (-1);
	if (j < 0 || !cube->map->final_grid[i][j] || cube->map->final_grid[i][j] == '\n')
		return (-1);
	if (is_a_wall(cube->map->final_grid[i][j]))
		return (0);
	if (cube->map->final_grid[i][j] == 'V')
		return (0);
	if (cube->map->final_grid[i][j] == ' ' || cube->map->final_grid[i][j] == '0')
		return (-1);
	if (!is_a_valid_char(cube->map->final_grid[i][j], AFTER_FF))
		return (-1);
	cube->map->final_grid[i][j] = 'V';
	if (vlood_vill(i + 1, j, cube) == -1)
		return (-1);
	if (vlood_vill(i - 1, j, cube) == -1)
		return (-1);
	if (vlood_vill(i, j + 1, cube) == -1)
		return (-1);
	if (vlood_vill(i, j - 1, cube) == -1)
		return (-1);
	return (0);
}