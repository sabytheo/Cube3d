/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:35:31 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/26 20:18:22 by egache           ###   ########.fr       */
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
		ft_printf_fd(2, E_BAD_FD);
		return (-1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf_fd(2, E_EMPTY_FILE);
		return (-1);
	}
	while (1)
	{
		if (!copy_line(cube, line))
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	check_arg(char *mapname)
{
	char	*s;

	s = ".cub\0";
	if (ft_strlen(mapname) < 5 || !ft_strchr(mapname, '.'))
	{
		ft_printf_fd(2, E_WRONG_EXT);
		return (-1);
	}
	if ((ft_strncmp(ft_strchr(mapname, '.'), s, 5)) != 0)
	{
		ft_printf_fd(2, E_WRONG_EXT);
		return (-1);
	}
	return (0);
}

//SKIP WHITESPACES DANS CETTE FONCTION
//CHECK

int	parse_textures_and_colors(t_game *cube, char **grid, int *i)
{
	while (grid[*i])
	{
		if (is_valid_texture(cube, grid, *i, ID_CHECK) == 0)
		{
			if (init_textures(i, grid, cube) < 0)
				return (-1);
			while (ft_strncmp("F ", grid[*i], 2) != 0 && ft_strncmp("C ", grid[*i],
				2) != 0)
			{
				if (!is_only_whitespace(i, grid))
					return (-1);
				(*i)++;
			}
			if (init_colors(i, grid, cube) < 0)
				return (-1);
			return (0);
		}
		else if (ft_strncmp("F ", grid[*i], 2) == 0 || ft_strncmp("C ",
				grid[*i], 2) == 0)
		{
			if (init_colors(i, grid, cube) < 0)
				return (-1);
			while (is_valid_texture(cube, grid, *i, ID_CHECK) < 0)
			{
				if (!is_only_whitespace(i, grid))
					return (-1);
				(*i)++;
			}
			if (init_textures(i, grid, cube) < 0)
				return (-1);
			return (0);
		}
		else if (!is_only_whitespace(i, grid))
		{
			ft_printf_fd(2, "Error\nWrong parameter\n");
			return (-1);
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
	if (parse_textures_and_colors(cube, cube->map.grid, &i))
		return (-1);
	if (parse_grid(&i, cube->map.grid, cube) < 0)
		return (-1);
	return (0);
}
