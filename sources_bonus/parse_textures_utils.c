/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:10:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/02 11:13:02 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	is_valid_texture(char **grid, int i)
{
	if (ft_strncmp("NO ", grid[i], 3) == 0 || ft_strncmp("SO ", grid[i], 3) == 0
		|| ft_strncmp("EA ", grid[i], 3) == 0 || ft_strncmp("WE ", grid[i],
			3) == 0 || ft_strncmp("DO ", grid[i], 3) == 0 || ft_strncmp("FL ",
			grid[i], 3) == 0 || ft_strncmp("CE ", grid[i], 3) == 0
		|| ft_strncmp("CL ", grid[i], 3) == 0)
		return (0);
	return (-1);
}
