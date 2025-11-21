/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:42:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/21 14:47:53 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	skip_textures_identifier(char **str)
{
	*str += 2;
	while (**str == ' ' || ((**str >= 9 && **str <= 13) && (**str != '\0')))
		(*str)++;
}

static int	copy_mandatory_textures(char *str, t_textures *textures)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && !textures->NO)
	{
		skip_textures_identifier(&str);
		textures->NO = ft_strdup(str);
		return (0);
	}
	else if (ft_strncmp(str, "SO ", 3) == 0 && !textures->SO)
	{
		skip_textures_identifier(&str);
		textures->SO = ft_strdup(str);
		return (0);
	}
	else if (ft_strncmp(str, "WE ", 3) == 0 && !textures->WE)
	{
		skip_textures_identifier(&str);
		textures->WE = ft_strdup(str);
		return (0);
	}
	else if (ft_strncmp(str, "EA ", 3) == 0 && !textures->EA)
	{
		skip_textures_identifier(&str);
		textures->EA = ft_strdup(str);
		return (0);
	}
	return (-1);
}

static int	copy_bonus_textures(char *str, t_textures *textures)
{
	if (ft_strncmp(str, "DO ", 3) == 0 && !textures->DO)
	{
		skip_textures_identifier(&str);
		textures->DO = ft_strdup(str);
		return (0);
	}
	else if (ft_strncmp(str, "FL ", 3) == 0 && !textures->FL)
	{
		skip_textures_identifier(&str);
		textures->FL = ft_strdup(str);
		return (0);
	}
	else if (ft_strncmp(str, "CE ", 3) == 0 && !textures->CE)
	{
		skip_textures_identifier(&str);
		textures->CE = ft_strdup(str);
		return (0);
	}
	else if (ft_strncmp(str, "SP ", 3) == 0 && !textures->SP)
	{
		skip_textures_identifier(&str);
		textures->SP = ft_strdup(str);
		return (0);
	}
	return (-1);
}

static int	is_valid_texture(t_game *cube, char **grid, int i, int status)
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
		if (!cube->textures.NO || !cube->textures.SO || !cube->textures.WE
			|| !cube->textures.EA || !cube->textures.DO || !cube->textures.FL
			|| !cube->textures.CE || !cube->textures.SP)
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
		if (is_valid_texture(cube, grid, *i, IDENTIFIER_CHECK) == 0)
		{
			if (copy_mandatory_textures(grid[*i], &cube->textures) == 0)
				count++;
			else if (copy_bonus_textures(grid[*i], &cube->textures) == 0)
				count++;
		}
		(*i)++;
		if (count == TEXTURES_FOUND)
		{
			if (is_valid_texture(cube, grid, *i, TEXTURE_EXIST) == -1)
			{
				printf(E_MISSING_TEXTURE);
				return (-1);
			}
			return (0);
		}
	}
	printf(E_MISSING_TEXTURE);
	return (-1);
}
