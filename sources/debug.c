/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:21:37 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/08 16:49:59 by tsaby            ###   ########.fr       */
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
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void print_width(t_gamestruct *cube)
{
	ft_printf("------------------------------------\n");
	ft_printf("height %d\n", cube->height);
	for (int i = 6; i < cube->height; i++)
	{
		ft_printf("width[%d] = %d\n",i,cube->width[i]);
	}
	ft_printf("------------------------------------\n");
	ft_printf("\n");
}
