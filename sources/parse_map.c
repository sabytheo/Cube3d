/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:35:31 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/08 16:53:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	copy_line(t_gamestruct *cube, char *line)
{
	char	**temp;
	int		i;

	if (!line)
		return (0);
	i = 0;
	cube->height++;
	temp = (char **)malloc(sizeof(char *) * (cube->height + 1));
	if (!temp)
	{
		free(line);
		free_exit(cube);
	}
	temp[cube->height] = NULL;
	while (i < cube->height - 1)
	{
		temp[i] = cube->map[i];
		i++;
	}
	temp[i] = line;
	if (cube->map)
		free(cube->map);
	cube->map = temp;
	return (1);
}

int	open_map(t_gamestruct *cube, char **argv)
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
int get_width(char ** map, t_gamestruct *cube)
{
	int i;
	int j;
	int len;

	i = 6;
	cube->width = malloc(sizeof(int) * (cube->height - 6 + 1));
	if (!cube->width)
		return (-1);
	while (map[i])
	{
		j = 0;
		len = 0;
		while(map[i][j])
		{
			while ((map[i][j] >= 9 && map[i][j] <= 13) || (map[i][j] == ' '))
				j++;
			len++;
			j++;
		}
		cube->width[i] = len - 1;
		i++;
	}
	return (0);
}

int	parse_map(t_gamestruct *cube, char **argv)
{
	if (open_map(cube, argv) < 0)
		return (-1);
	get_width(cube->map, cube);
	print_width(cube);
	print_map(cube->map);
	return (0);
}


