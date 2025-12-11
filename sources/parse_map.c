/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:35:31 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/11 15:56:44 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	open_map(t_game *cube, char **argv)
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

static int	check_arg(char *mapname)
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

static int	parse_textures_and_colors(t_game *cube, char **grid, int *i)
{
	while (grid[*i])
	{
		if (is_valid_texture(grid, *i) == 0)
		{
			if (init_textures_then_colors(cube, i, grid) < 0)
				return (-1);
			else
				return (0);
		}
		else if (ft_strncmp("F ", grid[*i], 2) == 0 || ft_strncmp("C ",
				grid[*i], 2) == 0)
		{
			if (init_colors_then_textures(cube, i, grid) < 0)
				return (-1);
			else
				return (0);
		}
		else if (!is_only_whitespace(i, grid))
		{
			ft_printf_fd(2, E_BEFORE_PARSING, grid[*i]);
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
