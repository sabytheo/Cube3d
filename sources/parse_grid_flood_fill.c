/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_flood_fill.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:49:13 by egache            #+#    #+#             */
/*   Updated: 2025/11/06 15:23:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	is_already_visited(char c)
{
	if (c == 'V' || c == '3')
		return (true);
	return (false);
}

char	replace_char(char c)
{
	if (is_a_player(c))
		return ('3');
	else if (c == '0')
		return ('V');
	return (c);
}

int	flood_fill(int i, int j, t_game *cube)
{
	if (i < 0 || i >= cube->map.grid_height || !cube->map.final_grid[i])
		return (-1);
	if (j < 0 || !cube->map.final_grid[i][j]
		|| cube->map.final_grid[i][j] == '\n')
		return (-1);
	if (is_a_wall(cube->map.final_grid[i][j]))
		return (0);
	if (is_already_visited(cube->map.final_grid[i][j]))
		return (0);
	if (!is_a_valid_char(cube->map.final_grid[i][j], GRID_CHECK))
		return (-1);
	cube->map.final_grid[i][j] = replace_char(cube->map.final_grid[i][j]);
	if (flood_fill(i + 1, j, cube) == -1)
		return (-1);
	if (flood_fill(i - 1, j, cube) == -1)
		return (-1);
	if (flood_fill(i, j + 1, cube) == -1)
		return (-1);
	if (flood_fill(i, j - 1, cube) == -1)
		return (-1);
	return (0);
}

// void	flood_fill(int i, int j, t_game *cube)
// {
// 	if (i < 0 || i >= cube->map.total_height || j < 0
// 		|| j >= cube->map.width[i])
// 		return ;
// 	while (cube->map.grid[i][j] == ' ' && cube->map.grid[i][j] != '\n')
// 		j++;
// 	if (is_a_player(cube->map.grid[i][j]))
// 		cube->map.grid[i][j] = '3';
// 	else if (cube->map.grid[i][j] == '0')
// 		cube->map.grid[i][j] = 'F';
// 	else
// 		return ;
// 	flood_fill(i + 1, j, cube);
// 	flood_fill(i - 1, j, cube);
// 	flood_fill(i, j + 1, cube);
// 	flood_fill(i, j - 1, cube);
// }
