/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:33:21 by tsaby             #+#    #+#             */
/*   Updated: 2025/09/30 19:20:05 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

void flood_fill(int i, int j, t_game *cube)
{
	if (i - cube->map->grid_start > cube->map->grid_height)
		cube->map->grid_height = i - cube->map->grid_start;
	// printf("i pos : %d || j pos : %d\n", i, j);
	if (i < 0 || i >= cube->map->total_height || j < 0 || j >= cube->map->width[i])
		return;
	while (cube->map->grid[i][j] == ' ' && cube->map->grid[i][j] != '\n')
		j++;
	if (cube->map->grid[i][j] == 'N' || cube->map->grid[i][j] == 'S' || cube->map->grid[i][j] == 'W' || cube->map->grid[i][j] == 'E')
		cube->map->grid[i][j] = '3';
	else if (cube->map->grid[i][j] == 'D')
		cube->map->grid[i][j] = '2';
	else if (cube->map->grid[i][j] == '0')
		cube->map->grid[i][j] = 'F';
	else
		return;
	flood_fill(i + 1, j, cube);
	flood_fill(i - 1, j, cube);
	flood_fill(i, j + 1, cube);
	flood_fill(i, j - 1, cube);
}

int copy_grid(t_game *cube)
{
	char **grid;
	int i;
	int j;

	grid = cube->map->grid;
	i = cube->map->grid_start;
	j = 0;

	cube->map->final_grid = malloc((cube->map->grid_height + 1) * sizeof(char *));
	if (!cube->map->final_grid)
		return (-1);
	while (grid[i] && j < cube->map->grid_height)
	{
		if (grid[i][0] == '\n')
			i++;
		cube->map->final_grid[j] = ft_strdup(grid[i++]);
		if (!cube->map->final_grid[j])
			return (-1); // free_tab;
		j++;
	}
	cube->map->final_grid[j] = NULL;
	printf("---------------------------------\n");
	print_map(cube->map->final_grid);
	printf("---------------------------------\n");
	return (1);
}

static bool is_a_valid_char(char c)
{
	if (c == 'F' || c == '3' || c == '1' || c == '2' || c == '\0')
		return (true);
	return (false);
}

int check_grid_validity(int i, int j, t_game *cube)
{
	printf("caca\n");
	if (is_a_valid_char(cube->map->final_grid[i][j]))
	{
		if (is_a_valid_char(cube->map->final_grid[i + 1][j]) && is_a_valid_char(cube->map->final_grid[i - 1][j]) && is_a_valid_char(cube->map->final_grid[i][j + 1]) && is_a_valid_char(cube->map->final_grid[i][j - 1]))
		{
			if (check_grid_validity(i + 1, j, cube) && check_grid_validity(i - 1, j, cube) && check_grid_validity(i, j + 1, cube) && check_grid_validity(i, j - 1, cube))
			{
				printf("cool 8-)\n");
				return (0);
			}
			printf("pas cool e_e\n");
			return (-1);
		}
	}
	printf("string : %s\n", cube->map->final_grid[i]);
	printf("char : %c\n", cube->map->final_grid[i][j]);
	printf("osef <_<'\n");
	return (1);
}

void parse_grid(int *i, char **grid, t_game *cube)
{
	int j;

	cube->map->grid_start = *i;
	while (grid[*i])
	{
		j = 0;
		while (grid[*i][j] != '\n')
		{
			if (grid[*i][j] == 'N' || grid[*i][j] == 'S' || grid[*i][j] == 'W' || grid[*i][j] == 'E')
			{
				cube->player->direction = grid[*i][j];
				cube->player->pos_x = *i;
				cube->player->pos_y = j;
				flood_fill(*i, j, cube);
				printf("grid_start : %d && grid_height : %d\n", cube->map->grid_start, cube->map->grid_height);
				copy_grid(cube);
				if (check_grid_validity(*i + cube->map->grid_start, j + cube->map->grid_start, cube) == -1)
				{
					printf("gros caca\n");
					return;
				}
				// printf("valeur de i en sortie de flood fill : %d\n", *i);
				// print_map(cube->map->grid);
				return;
			}
			j++;
		}
		(*i)++;
	}
}