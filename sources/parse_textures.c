/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:42:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/04 15:25:32 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	skip_textures_identifier(char **str)
{
	*str += 2;
	while (**str == ' ' || ((**str >= 9 && **str <= 13) && (**str != '\0')))
		(*str)++;
}

int	copy_textures(char *str, t_texture *textures)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && !textures->NO)
	{
		skip_textures_identifier(&str);
		textures->NO = ft_strdup(str);
	}
	else if (ft_strncmp(str, "SO ", 3) == 0 && !textures->SO)
	{
		skip_textures_identifier(&str);
		textures->SO = ft_strdup(str);
	}
	else if (ft_strncmp(str, "WE ", 3) == 0 && !textures->WE)
	{
		skip_textures_identifier(&str);
		textures->WE = ft_strdup(str);
	}
	else if (ft_strncmp(str, "EA ", 3) == 0 && !textures->EA)
	{
		skip_textures_identifier(&str);
		textures->EA = ft_strdup(str);
	}
	else
		return (-1);
	return (0);
}

static int	get_textures(char *str, t_texture *textures, int i)
{
	if (copy_textures(str, textures) == -1)
	{
		ft_printf(E_ALREADY_FOUND);
		return (-1);
	}
	if (i == 3)
	{
		if (!textures->NO || !textures->SO || !textures->WE || !textures->EA)
		{
			printf("allo\n");
			return (-1);
		}
	}
	return (0);
}

int	init_textures(int *i, char **grid, t_game *cube)
{
	int	count;

	count = 0;
	while (grid[*i])
	{
		if (ft_strncmp("NO ", grid[*i], 3) == 0 || ft_strncmp("SO ", grid[*i],
				3) == 0 || ft_strncmp("EA ", grid[*i], 3) == 0
			|| ft_strncmp("WE ", grid[*i], 3) == 0)
		{
			if (get_textures(grid[*i], &cube->textures, count) < 0)
				return (-1);
			count++;
		}
		(*i)++;
		if (count == TEXTURES_FOUND)
		{
			return (0);
		}
	}
	return (-1);
}
