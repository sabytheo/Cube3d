/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:10:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/21 17:19:49 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	is_valid_texture(t_game *cube, char **grid, int i, int status)
{
	if (status)
	{
		if (ft_strncmp("NO ", grid[i], 3) == 0 || ft_strncmp("SO ", grid[i],
				3) == 0 || ft_strncmp("EA ", grid[i], 3) == 0
			|| ft_strncmp("WE ", grid[i], 3) == 0 || ft_strncmp("DO ", grid[i],
				3) == 0 || ft_strncmp("FL ", grid[i], 3) == 0
			|| ft_strncmp("CE ", grid[i], 3) == 0 || ft_strncmp("SP ", grid[i],
				3) == 0)
			return (0);
		return (-1);
	}
	else
	{
		if (!cube->textures.NO || !cube->textures.WE || !cube->textures.EA
			|| !cube->textures.DO || !cube->textures.FL || !cube->textures.CE
			|| !cube->textures.SP)
			return (-1);
		return (0);
	}
}
