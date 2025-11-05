/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:47:21 by egache            #+#    #+#             */
/*   Updated: 2025/11/05 19:42:17 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

	if (state == CHAR_CHECK)
	{
		if (c == '0' || c == '1' || c == 'D' || c == ' ' || c == 'L')
			return (true);
		else if (is_a_player(c) && found_player == false)
		{
			found_player = true;
			return (true);
		}
		else
			return (false);
	}
	if (state == GRID_CHECK)
	{
		if (c == 'D' || c == '0' || c == '1' || is_a_player(c))
			return (true);
		return (false);
	}
	return (true);
}
