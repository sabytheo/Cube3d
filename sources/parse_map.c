/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:35:31 by tsaby             #+#    #+#             */
/*   Updated: 2025/09/25 16:10:18 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

static int	copy_line(t_game *cube, char *line)
{
	char	**temp;
	int		i;

	if (!line)
		return (0);
	i = 0;
	cube->map->height++;
	temp = (char **)malloc(sizeof(char *) * (cube->map->height + 1));
	if (!temp)
	{
		free(line);
		free_exit(cube);
	}
	temp[cube->map->height] = NULL;
	while (i < cube->map->height - 1)
	{
		temp[i] = cube->map->grid[i];
		i++;
	}
	temp[i] = line;
	if (cube->map->grid)
		free(cube->map->grid);
	cube->map->grid = temp;
	return (1);
}

int	open_map(t_game *cube, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error\n");
		return (-1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!copy_line(cube, line))
			break ;
	}
	close(fd);
	return (0);
}
int	get_width(char **map, t_game *cube)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	cube->map->width = malloc(sizeof(int) * (cube->map->height + 1));
	if (!cube->map->width)
		return (-1);
	while (map[i])
	{
		j = 0;
		len = 0;
		while (map[i][j] != '\n')
		{
			while ((map[i][j] >= 9 && map[i][j] <= 13) || (map[i][j] == ' '))
				j++;
			len++;
			j++;
		}
		cube->map->width[i] = len - 1;
		if (cube->map->width[i] > cube->map->max_width)
			cube->map->max_width = cube->map->width[i];
		i++;
	}
	return (0);
}
int	check_arg(char *mapname)
{
	char	*s;

	s = ".cub\0";
	if ((ft_strncmp(ft_strchr(mapname, '.'), s, 5)) != 0)
	{
		ft_printf_fd(2, E_WRONG_EXT);
		return (-1);
	}
	return (0);
}


int	parse_map(t_game *cube, char **argv)
{
	if (check_arg(argv[1]) < 0)
		return (-1);
	if (open_map(cube, argv) < 0)
		return (-1);
	get_width(cube->map->grid, cube);
	if (init_textures(cube->map->grid,cube) < 0)
		return (-1);
	if (init_colors(cube->map->grid,cube) < 0)
		return (-1);
	// print_width(cube);
	// print_map(cube->map->grid);
	print_texture(cube->textures);
	return (0);
}
