/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:33:21 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/02 20:26:06 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

void flood_fill(int i, int j, t_game *cube)
{
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
		// if (grid[i][0] == '\n')
		// 	i++;
		cube->map->final_grid[j] = ft_strdup(grid[i++]);
		if (!cube->map->final_grid[j])
			return (-1);
		j++;
	}
	cube->map->final_grid[j] = NULL;
	printf("\n---------------------------------\n");
	print_map(cube->map->final_grid);
	printf("\n---------------------------------\n");
	return (1);
}

static bool is_only_whitespace(int *i, char **grid)
{
	int j;

	j = 0;
	while (grid[*i][j] && grid[*i][j] != '\n')
	{
		if ((grid[*i][j] <= 9 || grid[*i][j] >= 13) && grid[*i][j] != ' ')
			return (false);
		j++;
	}
	return (true);
}

static bool is_a_valid_char(char c)
{
	if (c == 'F' || c == '2' || c == '3')
		return (true);
	return (false);
}

static bool is_a_wall(char c)
{
	if (c == '1')
		return (true);
	return (false);
}

int check_grid_validity(int i, int j, t_game *cube)
{
	if (i < 0 || i >= cube->map->grid_height || !cube->map->final_grid[i])
		return (-1);
	if (j < 0 || !cube->map->final_grid[i][j] || cube->map->final_grid[i][j] == '\n')
		return (-1);
	if (is_a_wall(cube->map->final_grid[i][j]))
		return (0);
	if (cube->map->final_grid[i][j] == 'V')
		return (0);
	if (cube->map->final_grid[i][j] == ' ' || cube->map->final_grid[i][j] == '0')
		return (-1);
	if (!is_a_valid_char(cube->map->final_grid[i][j]))
		return (-1);
	cube->map->final_grid[i][j] = 'V';
	if (check_grid_validity(i + 1, j, cube) == -1)
		return (-1);
	if (check_grid_validity(i - 1, j, cube) == -1)
		return (-1);
	if (check_grid_validity(i, j + 1, cube) == -1)
		return (-1);
	if (check_grid_validity(i, j - 1, cube) == -1)
		return (-1);
	return (0);
}

void parse_grid(int *i, char **grid, t_game *cube)
{
	int j;

	while (grid[*i] && is_only_whitespace(i, grid))
		(*i)++;
	cube->map->grid_start = *i;
	// printf("i dans parse grid avant : %d\n", *i);
	cube->map->grid_height = cube->map->total_height - cube->map->grid_start;
	printf("%d - %d = %d >? %d\n", cube->map->total_height, cube->map->grid_start, (cube->map->total_height - cube->map->grid_start), cube->map->grid_height);
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
				// FAIRE VERIFICATION BONS CHARS (NE PAS ACCEPTER V PAR EXEMPLE AU PIF AU HASARD VRAIMENT)
				// printf("total_height dans parse grid avant flood fill : %d\n", cube->map->total_height);
				// printf("grid_height  dans parse grid avant flood fill : %d\n", cube->map->grid_height);
				flood_fill(*i, j, cube);
				copy_grid(cube);
				if (check_grid_validity(*i - cube->map->grid_start, j, cube) == -1)
				{
					printf("gros caca\n");
					print_map(cube->map->final_grid);
					return;
				}
				printf("t cool map 8-)\n");
				print_map(cube->map->final_grid);
				return;
			}
			j++;
		}
		(*i)++;
	}
}

// static bool is_a_valid_char(char c)
// {
// 	if (c == 'F' || c == '3' || c == '1' || c == '2' || c == '\0')
// 		return (true);
// 	return (false);
// }

// int check_grid_validity(int i, int j, t_game *cube)
// {
// 	printf("caca\n");
// 	if (is_a_valid_char(cube->map->final_grid[i][j]))
// 	{
// 		if (is_a_valid_char(cube->map->final_grid[i + 1][j]) && is_a_valid_char(cube->map->final_grid[i - 1][j]) && is_a_valid_char(cube->map->final_grid[i][j + 1]) && is_a_valid_char(cube->map->final_grid[i][j - 1]))
// 		{
// 			if (check_grid_validity(i + 1, j, cube) && check_grid_validity(i - 1, j, cube) && check_grid_validity(i, j + 1, cube) && check_grid_validity(i, j - 1, cube))
// 			{
// 				printf("cool 8-)\n");
// 				return (0);
// 			}
// 			printf("pas cool e_e\n");
// 			return (-1);
// 		}
// 	}
// 	printf("string : %s\n", cube->map->final_grid[i]);
// 	printf("char : %c\n", cube->map->final_grid[i][j]);
// 	printf("osef <_<'\n");
// 	return (1);
// }