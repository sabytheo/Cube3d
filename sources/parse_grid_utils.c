/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:47:21 by egache            #+#    #+#             */
/*   Updated: 2025/11/25 16:05:15 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_width(char **map, t_game *cube, int i)
{
	int	j;
	int	len;

	cube->map.width = malloc(sizeof(int) * (cube->map.total_height + 1));
	if (!cube->map.width)
		return (-1);
	while (map[i])
	{
		j = 0;
		len = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			len++;
			j++;
		}
		cube->map.width[i] = len - 1;
		if (cube->map.width[i] > cube->map.max_width)
			cube->map.max_width = cube->map.width[i];
		if (len > 100 || i - cube->map.grid_start > 50)
			return (-1);
		i++;
	}
	return (0);
}

void	get_angle(t_game *cube, char c)
{
	if (c == 'N')
		cube->player.angle = M_PI / 2;
	else if (c == 'S')
		cube->player.angle = -M_PI / 2;
	else if (c == 'W')
		cube->player.angle = M_PI;
	else if (c == 'E')
		cube->player.angle = 0;
	return ;
}

bool	is_only_whitespace(int *i, char **grid)
{
	int	j;

	j = 0;
	while (grid[*i][j] && grid[*i][j] != '\n')
	{
		if ((grid[*i][j] <= 9 || grid[*i][j] >= 13) && grid[*i][j] != ' ')
			return (false);
		j++;
	}
	return (true);
}

bool	is_a_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	is_a_valid_char(t_game *cube, char c, bool state)
{
	if (state == CHAR_CHECK)
	{
		if (c == '0' || c == '1' || c == ' ')
			return (true);
		else if (is_a_player(c) && cube->player.found == false)
		{
			cube->player.found = true;
			return (true);
		}
		else
			return (false);
	}
	if (state == GRID_CHECK)
	{
		if (c == '0' || c == '1' || is_a_player(c))
			return (true);
		return (false);
	}
	return (true);
}
