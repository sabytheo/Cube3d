/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:21:37 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/19 18:31:31 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		// ft_printf("[%d] :", i);
		ft_printf("%s", map[i]);
		i++;
	}
}

void print_width(t_game *cube)
{
	ft_printf("------------------------------------\n");
	for (int i = 6; i < cube->map->height; i++)
	{
		ft_printf("width[%d] = %d\n",i,cube->map->width[i]);
	}
	ft_printf("------------------------------------\n");
	ft_printf("Max width = %d\n", cube->map->max_width);
	ft_printf("Height =  %d\n", cube->map->height - 6);
	ft_printf("------------------------------------\n");
	ft_printf("\n");
}
