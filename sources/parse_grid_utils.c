/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:47:21 by egache            #+#    #+#             */
/*   Updated: 2025/11/04 15:25:22 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

bool	is_a_wall(char c)
{
	if (c == '1')
		return (true);
	return (false);
}

bool	is_a_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	is_a_valid_char(char c, bool state)
{
	static bool	found_player = 0;

	if (state == BEFORE_FF)
	{
		if (c == '0' || c == '1' || c == ' ')
			return (true);
		else if (is_a_player(c) && found_player == false)
		{
			found_player = true;
			return (true);
		}
		else
			return (false);
	}
	if (state == AFTER_FF)
	{
		if (c == 'F' || c == 'C' || c == '3')
			return (true);
		return (false);
	}
	return (true);
}
