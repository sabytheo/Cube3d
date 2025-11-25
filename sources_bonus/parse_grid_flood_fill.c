/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_flood_fill.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:49:13 by egache            #+#    #+#             */
/*   Updated: 2025/11/25 16:28:30 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static bool	is_a_wall(char c)
{
	if (c == '1')
		return (true);
	return (false);
}

static bool	is_already_visited(char c)
{
	if (c == 'V' || c == 'C' || c == '3')
		return (true);
	return (false);
}

static char	replace_char(char c)
{
	if (is_a_player(c))
		return ('3');
	else if (c == '0')
		return ('V');
	else if (c == 'D')
		return ('C');
	return (c);
}

bool	is_surrounded(t_game *cube, int i, int j)
{
	if ((cube->map.final_grid[i + 1][j] == '1' && cube->map.final_grid[i
			- 1][j] == '1') || (cube->map.final_grid[i][j + 1] == '1'
			&& cube->map.final_grid[i][j - 1] == '1'))
		return (true);
	return (false);
}

int	flood_fill(int i, int j, t_game *cube)
{
	if (i < 0 || i >= cube->map.grid_height || !cube->map.final_grid[i])
		return (-1);
	if (j < 0 || !cube->map.final_grid[i] || !cube->map.final_grid[i][j]
		|| cube->map.final_grid[i][j] == '\n')
			return (-1);
	if (is_a_wall(cube->map.final_grid[i][j]))
		return (0);
	if (is_already_visited(cube->map.final_grid[i][j]))
		return (0);
	if (cube->map.final_grid[i][j] == 'D')
	{
		if (!is_surrounded(cube, i, j))
			return (-1);
	}
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
// 	else if (cube->map.grid[i][j] == 'D')
// 		cube->map.grid[i][j] = 'C';
// 	else if (cube->map.grid[i][j] == '0')
// 		cube->map.grid[i][j] = 'F';
// 	else
// 		return ;
// 	flood_fill(i + 1, j, cube);
// 	flood_fill(i - 1, j, cube);
// 	flood_fill(i, j + 1, cube);
// 	flood_fill(i, j - 1, cube);
// }

// int	vlood_vill(int i, int j, t_game *cube)
// {
// 	if (i < 0 || i >= cube->map.grid_height || !cube->map.final_grid[i])
// 		return (-1);
// 	if (j < 0 || !cube->map.final_grid[i][j]
// 		|| cube->map.final_grid[i][j] == '\n')
// 		return (-1);
// 	if (is_a_wall(cube->map.final_grid[i][j]))
// 		return (0);
// 	if (cube->map.final_grid[i][j] == 'V' || cube->map.final_grid[i][j] == 'O'
// 		|| cube->map.final_grid[i][j] == 'L')
// 		return (0);
// 	if (cube->map.final_grid[i][j] == ' '
// 		|| cube->map.final_grid[i][j] == '0')
// 		return (-1);
// 	if (!is_a_valid_char(cube->map.final_grid[i][j], GRID_CHECK))
// 		return (-1);
// 	if (cube->map.final_grid[i][j] != 'C')
// 		cube->map.final_grid[i][j] = 'V';
// 	if (vlood_vill(i + 1, j, cube) == -1)
// 		return (-1);
// 	if (vlood_vill(i - 1, j, cube) == -1)
// 		return (-1);
// 	if (vlood_vill(i, j + 1, cube) == -1)
// 		return (-1);
// 	if (vlood_vill(i, j - 1, cube) == -1)
// 		return (-1);
// 	return (0);
// }
