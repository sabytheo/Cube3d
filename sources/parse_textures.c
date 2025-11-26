/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:42:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/26 21:39:46 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	skip_textures_identifier(char **str)
{
	*str += 2;
	while (**str == ' ' || ((**str >= 9 && **str <= 13) && (**str != '\0')))
		(*str)++;
}

static int	cp_mand_textures(char *str, t_textures *textures)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && !textures->NO)
	{
		skip_textures_identifier(&str);
		textures->NO = ft_strdup_no_whitespace(str);
		return (0);
	}
	else if (ft_strncmp(str, "SO ", 3) == 0 && !textures->SO)
	{
		skip_textures_identifier(&str);
		textures->SO = ft_strdup_no_whitespace(str);
		return (0);
	}
	else if (ft_strncmp(str, "WE ", 3) == 0 && !textures->WE)
	{
		skip_textures_identifier(&str);
		textures->WE = ft_strdup_no_whitespace(str);
		return (0);
	}
	else if (ft_strncmp(str, "EA ", 3) == 0 && !textures->EA)
	{
		skip_textures_identifier(&str);
		textures->EA = ft_strdup_no_whitespace(str);
		return (0);
	}
	return (-1);
}

int	is_valid_texture(t_game *cube, char **grid, int i, int status)
{
	if (status == ID_CHECK)
	{
		if (ft_strncmp("NO ", grid[i], 3) == 0 || ft_strncmp("SO ", grid[i],
				3) == 0 || ft_strncmp("EA ", grid[i], 3) == 0
			|| ft_strncmp("WE ", grid[i], 3) == 0)
			return (0);
		return (-1);
	}
	else
	{
		if (!cube->textures.NO || !cube->textures.SO || !cube->textures.WE
			|| !cube->textures.EA)
			return (-1);
		return (0);
	}
}

int	init_textures(int *i, char **grid, t_game *cube)
{
	int	count;

	count = 0;
	while (grid[*i])
	{
		if (is_valid_texture(cube, grid, *i, ID_CHECK) == 0)
		{
			if (cp_mand_textures(grid[*i], &cube->textures) < 0)
				return (-1);
			count++;
		}
		else if (!is_only_whitespace(i, grid))
		{
			ft_printf_fd(2, E_PARSING_TEXTURES);
			return (-1);
		}
		(*i)++;
		if (count == TEXTURES_FOUND)
		{
			if (is_valid_texture(cube, grid, *i, TEXTURE_EXIST) == -1)
			{
				ft_printf_fd(2, E_PARSING_TEXTURES);
				return (-1);
			}
			return (0);
		}
	}
	ft_printf_fd(2, E_PARSING_TEXTURES);
	return (-1);
}
