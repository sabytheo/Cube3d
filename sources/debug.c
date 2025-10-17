/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:21:37 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/17 12:28:55 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		// ft_printf("[%d] :", i);
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void	print_texture(t_texture *textures)
{
	int	i;

	i = 0;
	printf("texture NO : |%s|\n", textures->NO);
	printf("texture SO : |%s|\n", textures->SO);
	printf("texture WE : |%s|\n", textures->WE);
	printf("texture EA : |%s|\n", textures->EA);
	while (i < 3)
	{
		printf("texture C : %d\n", textures->ceiling[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("texture F : %d\n", textures->floor[i]);
		i++;
	}
}

void	print_width(t_game *cube)
{
	ft_printf("------------------------------------\n");
	for (int i = 6; i < cube->map->total_height; i++)
	{
		ft_printf("width[%d] = %d\n", i, cube->map->width[i]);
	}
	ft_printf("------------------------------------\n");
	ft_printf("Max width = %d\n", cube->map->max_width);
	ft_printf("Height =  %d\n", cube->map->total_height - 6);
	ft_printf("------------------------------------\n");
	ft_printf("\n");
}
