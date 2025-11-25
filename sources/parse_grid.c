/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:33:21 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/25 16:20:09 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>

static int	copy_grid(t_game *cube)
{
	char	**grid;
	int		i;
	int		j;

	grid = cube->map.grid;
	i = cube->map.grid_start;
	j = 0;
	cube->map.final_grid = malloc((cube->map.grid_height + 1) * sizeof(char *));
	if (!cube->map.final_grid)
		return (-1);
	while (grid[i] && j < cube->map.grid_height)
	{
		cube->map.final_grid[j] = ft_strdup(grid[i++]);
		if (!cube->map.final_grid[j])
			return (-1);
		j++;
	}
	cube->map.final_grid[j] = NULL;
	return (1);
}

static int	check_char_validity(t_game *cube)
{
	size_t	i;
	size_t	j;
	char	**grid;

	i = cube->map.grid_start;
	j = 0;
	grid = cube->map.grid;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j] && grid[i][j] != '\n')
		{
			if (!is_a_valid_char(cube, grid[i][j], CHAR_CHECK))
			{
				ft_printf_fd(2, E_BAD_CHAR_PARSING);
				return (-1);
			}
			j++;
		}
		i++;
	}
	if (cube->player.found == true)
		return (0);
	ft_printf_fd(2, E_MISSING_PLAYER);
	return (-1);
}

static void	set_player_info(int i, int j, t_game *cube)
{
	cube->player.direction = cube->map.grid[i][j];
	get_angle(cube, cube->player.direction);
	cube->player.tan_fov_2 = tan(cube->player.fov * 0.5);
	cube->player.pos_y = (i - cube->map.grid_start) + 0.5;
	cube->player.pos_x = j + 0.5;
	return ;
}

static int	check_grid_validity(int *i, t_game *cube)
{
	int	j;

	while (cube->map.grid[*i])
	{
		j = 0;
		while (cube->map.grid[*i][j] != '\n')
		{
			if (is_a_player(cube->map.grid[*i][j]))
			{
				set_player_info(*i, j, cube);
				if (copy_grid(cube) < 0)
					return (-1);
				if (flood_fill(*i - cube->map.grid_start, j, cube) < 0)
				{
					ft_printf_fd(2, E_BAD_GRID_PARSING);
					return (-1);
				}
				return (0);
			}
			j++;
		}
		(*i)++;
	}
	return (0);
}

int	parse_grid(int *i, char **grid, t_game *cube)
{
	while (grid[*i] && is_only_whitespace(i, grid))
		(*i)++;
	if (grid[*i])
	{
		cube->map.grid_start = *i;
		cube->map.grid_height = cube->map.total_height - cube->map.grid_start;
		if (get_width(cube->map.grid, cube, *i) < 0)
		{
			printf(E_BAD_MAP_SIZE);
			return (-1);
		}
		if (check_char_validity(cube) < 0)
			return (-1);
		if (check_grid_validity(i, cube) < 0)
			return (-1);
		return (0);
	}
	printf(E_BAD_GRID_MISSING);
	return (-1);
}
