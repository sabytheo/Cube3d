/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_flood_fill.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:49:13 by egache            #+#    #+#             */
/*   Updated: 2025/11/27 18:31:11 by egache           ###   ########.fr       */
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

static bool	is_surrounded(t_game *cube, int i, int j)
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
