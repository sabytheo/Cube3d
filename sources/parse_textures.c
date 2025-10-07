/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:42:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/07 12:35:02 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void skip_textures_identifier(char **str)
{
	*str += 2;
	while (**str == ' ' || ((**str >= 9 && **str <= 13) && (**str != '\0')))
		(*str)++;
}

int copy_textures(char *str, t_texture *textures)
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

static int get_textures(char *str, t_texture *textures, int i)
{
	if (copy_textures(str, textures) == -1)
	{
		ft_printf(E_ALREADY_FOUND);
		return (-1);
	}
	if (i == 3)
	{
		if (!textures->NO || !textures->SO || !textures->WE || !textures->EA)
			return (-1);
	}
	return (0);
}

int init_textures(int *i, char **grid, t_game *cube)
{
	t_texture *textures;
	int count;

	textures = (t_texture *)ft_calloc(1, sizeof(t_texture));
	count = 0;
	while (grid[*i])
	{
		if (ft_strncmp("NO ", grid[*i], 3) == 0 || ft_strncmp("SO ", grid[*i], 3) == 0 || ft_strncmp("EA ", grid[*i], 3) == 0 || ft_strncmp("WE ", grid[*i], 3) == 0)
		{
			if (get_textures(grid[*i], textures, count) < 0)
				return (-1);
			count++;
		}
		(*i)++;
		// printf("i dans textures : %d\n", *i);
		cube->textures = textures;
		if (count == TEXTURES_FOUND)
		{
			return (0);
		}
	}
	return (-1);
}

int check_len_and_skip_space(char **str, int *j, int *len)
{
	if (*j > 2)
	{
		ft_printf(E_BAD_COLOR_USAGE);
		return (-1);
	}
	(*str)++;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	while (**str && **str != '\n' && **str != ',')
	{
		(*len)++;
		(*str)++;
	}
	if (*len > 3 || *len == 0)
	{
		ft_printf(E_BAD_COLOR_USAGE);
		return (-1);
	}
	(*str) -= (*len);
	return (0);
}

int get_ceiling_values(char **str, int *len, t_texture *textures)
{
	char *tmp;
	int j;

	j = 0;
	while (**str && **str != '\n')
	{
		*len = 0;
		if (check_len_and_skip_space(str, &j, len) < 0)
			return (-1);
		tmp = ft_strldup(*str, *len);
		textures->ceiling[j] = ft_atoi(tmp);
		free(tmp);
		tmp = NULL;
		if (textures->ceiling[j] > 255)
		{
			ft_printf(E_BAD_COLOR_USAGE);
			return (-1);
		}
		*str += *len;
		j++;
	}
	return (0);
}

int get_floor_values(char **str, int *len, t_texture *textures)
{
	char *tmp;
	int j;

	j = 0;
	while (**str && **str != '\n')
	{
		*len = 0;
		if (check_len_and_skip_space(str, &j, len) < 0)
			return (-1);
		tmp = ft_strldup(*str, *len);
		textures->floor[j] = ft_atoi(tmp);
		free(tmp);
		tmp = NULL;
		if (textures->floor[j] > 255)
		{
			ft_printf(E_BAD_COLOR_USAGE);
			return (-1);
		}
		*str += *len;
		j++;
	}
	return (0);
}

static int get_colors(char *str, t_texture *textures)
{
	int len;

	len = 0;
	if (ft_strncmp(str, "F ", 2) == 0 && !textures->floor[0])
	{
		if (get_floor_values(&str, &len, textures) < 0)
			return (-1);
	}
	else if (ft_strncmp(str, "C ", 2) == 0 && !textures->ceiling[0])
	{
		if (get_ceiling_values(&str, &len, textures) < 0)
			return (-1);
	}
	else
		return (1);
	return (0);
}

int init_colors(int *i, char **grid, t_game *cube)
{
	int count;

	count = 0;
	while (grid[*i])
	{
		if (ft_strncmp("F ", grid[*i], 2) == 0 || ft_strncmp("C ", grid[*i],
															 2) == 0)
		{
			if (get_colors(grid[*i], cube->textures) < 0)
				return (-1);
			count++;
		}
		(*i)++;
		if (count == COLORS_FOUND)
			return (0);
	}
	return (-1);
}

// int init_colors(int *i, char **grid, t_game *cube)
// {
// 	int count;
// 	int ret;

// 	count = 0;
// 	while (grid[*i])
// 	{
// 		ret = get_colors(grid[*i], cube->textures, count);
// 		if (ret < 0)
// 			return (-1);
// 		else if (ret == 0)
// 			count++;
// 		printf("i dans colors : %d\n", *i);
// 		if (count == COLORS_FOUND)
// 			return (0);
// 		(*i)++;
// 	}
// 	return (-1);
// }