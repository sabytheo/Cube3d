/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:20:16 by egache            #+#    #+#             */
/*   Updated: 2025/12/11 15:59:15 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	copy_line(t_game *cube, char *line)
{
	char	**temp;
	int		i;

	if (!line)
		return (0);
	i = 0;
	cube->map.total_height++;
	temp = (char **)malloc(sizeof(char *) * (cube->map.total_height + 1));
	if (!temp)
	{
		free(line);
		free_exit(cube);
	}
	temp[cube->map.total_height] = NULL;
	while (i < cube->map.total_height - 1)
	{
		temp[i] = cube->map.grid[i];
		i++;
	}
	temp[i] = line;
	if (cube->map.grid)
		free(cube->map.grid);
	cube->map.grid = temp;
	return (1);
}

int	init_textures_then_colors(t_game *cube, int *i, char **grid)
{
	if (init_textures(i, grid, cube) < 0)
		return (-1);
	while (grid[*i] && ft_strncmp("F ", grid[*i], 2) != 0
		&& ft_strncmp("C ", grid[*i], 2) != 0)
	{
		if (!is_only_whitespace(i, grid))
		{
			ft_printf_fd(2, E_BAD_COLOR_PARSING, grid[*i]);
			return (-1);
		}
		(*i)++;
	}
	if (init_colors(i, grid, cube) < 0)
		return (-1);
	return (0);
}

int	init_colors_then_textures(t_game *cube, int *i, char **grid)
{
	if (init_colors(i, grid, cube) < 0)
		return (-1);
	while (grid[*i] && is_valid_texture(grid, *i) < 0)
	{
		if (!is_only_whitespace(i, grid))
		{
			ft_printf_fd(2, E_BAD_TEXT_PARSING, grid[*i]);
			return (-1);
		}
		(*i)++;
	}
	if (init_textures(i, grid, cube) < 0)
		return (-1);
	return (0);
}
