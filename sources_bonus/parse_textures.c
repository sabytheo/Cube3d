/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:42:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/25 16:48:35 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	skip_textures_identifier(char **str)
{
	*str += 2;
	while (**str == ' ' || ((**str >= 9 && **str <= 13) && (**str != '\0')))
		(*str)++;
}

static int	cp_mand_textures(char *str, t_textures *textures, int *so_count)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && !textures->NO)
	{
		skip_textures_identifier(&str);
		textures->NO = ft_strdup_no_whitespace(str);
		return (0);
	}
	else if (ft_strncmp(str, "SO ", 3) == 0 && *so_count < 6)
	{
		skip_textures_identifier(&str);
		textures->SO[(*so_count)++] = ft_strdup_no_whitespace(str);
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

static int	copy_bonus_textures(char *str, t_textures *textures)
{
	if (ft_strncmp(str, "DO ", 3) == 0 && !textures->DO)
	{
		skip_textures_identifier(&str);
		textures->DO = ft_strdup_no_whitespace(str);
		return (0);
	}
	else if (ft_strncmp(str, "FL ", 3) == 0 && !textures->FL)
	{
		skip_textures_identifier(&str);
		textures->FL = ft_strdup_no_whitespace(str);
		return (0);
	}
	else if (ft_strncmp(str, "CE ", 3) == 0 && !textures->CE)
	{
		skip_textures_identifier(&str);
		textures->CE = ft_strdup_no_whitespace(str);
		return (0);
	}
	else if (ft_strncmp(str, "SP ", 3) == 0 && !textures->SP)
	{
		skip_textures_identifier(&str);
		textures->SP = ft_strdup_no_whitespace(str);
		return (0);
	}
	return (-1);
}

static int	check_textures(t_game *cube, int so_count, char **grid, int *i)
{
	if (so_count != 6)
	{
		printf(E_MISSING_TEXTURE);
		return (-1);
	}
	if (is_valid_texture(cube, grid, *i, TEXTURE_EXIST) == -1)
	{
		printf(E_MISSING_TEXTURE);
		return (-1);
	}
	return (0);
}

int	init_textures(int *i, char **grid, t_game *cube)
{
	int	count;
	int	so_count;

	so_count = 0;
	count = 0;
	while (grid[*i])
	{
		if (is_valid_texture(cube, grid, *i, ID_CHECK) == 0)
		{
			if (cp_mand_textures(grid[*i], &cube->textures, &so_count) == 0)
				count++;
			else if (copy_bonus_textures(grid[*i], &cube->textures) == 0)
				count++;
		}
		(*i)++;
		if (count == TEXTURES_FOUND + 5)
		{
			if (check_textures(cube, so_count, grid, i) < 0)
				return (-1);
			while (grid[*i] && (!is_valid_texture(cube, grid, *i, ID_CHECK)))
				(*i)++;
			return (0);
		}
	}
	return (-1);
}
