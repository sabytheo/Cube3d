/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:20:16 by egache            #+#    #+#             */
/*   Updated: 2025/11/21 16:20:47 by egache           ###   ########.fr       */
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
