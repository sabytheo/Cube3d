/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:35:31 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/21 17:42:19 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
		if (len > 100 || i > 50)
			return (-1);
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

int	parse_textures_and_colors(t_game *cube, char **grid, int *i)
{
	while (grid[*i])
	{
		while (grid[*i] && is_only_whitespace(i, grid))
			(*i)++;
		if (is_valid_texture(cube, grid, *i, ID_CHECK) == 0)
		{
			if (init_textures(i, grid, cube) < 0)
				return (-1);
			if (init_colors(i, grid, cube) < 0)
				return (-1);
			return (0);
		}
		else if (ft_strncmp("F ", grid[*i], 2) == 0 || ft_strncmp("C ",
				grid[*i], 2) == 0)
		{
			if (init_colors(i, grid, cube) < 0)
				return (-1);
			if (init_textures(i, grid, cube) < 0)
				return (-1);
			return (0);
		}
		(*i)++;
	}
	return (-1);
}

int	parse_map(t_game *cube, char **argv)
{
	int	i;

	i = 0;
	if (check_arg(argv[1]) < 0)
		return (-1);
	if (open_map(cube, argv) < 0)
		return (-1);
	if (get_width(cube->map.grid, cube) < 0)
	{
		printf(E_BAD_MAP_SIZE);
		return (-1);
	}
	if (parse_textures_and_colors(cube, cube->map.grid, &i))
		return (-1);
	if (parse_grid(&i, cube->map.grid, cube) < 0)
		return (-1);
	print_map(cube->map.final_grid);
	return (0);
}
