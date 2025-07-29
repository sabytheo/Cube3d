/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:35:31 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/29 20:28:25 by tsaby            ###   ########.fr       */
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
	cube->hmap++;
	temp = (char **)malloc(sizeof(char *) * (cube->hmap + 1));
	if (!temp)
	{
		free(line);
		free_exit(cube);
	}
	temp[cube->hmap] = NULL;
	while (i < cube->hmap - 1)
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

	cube->fd = open(argv[1], O_RDONLY);
	if (cube->fd < 0)
	{
		ft_printf_fd(2, "Error\n");
		return (-1);
	}
	while (1)
	{
		line = get_next_line(cube->fd);
		if (!copy_line(cube, line))
			break ;
	}
	close(cube->fd);
	return (0);
}

int	init_map(t_gamestruct *cube, char **argv)
{
	if (open_map(cube, argv) < 0)
		return (-1);
	print_map(cube->map);
	return (0);
}
