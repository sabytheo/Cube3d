/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:42:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/09/25 18:10:50 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

static int	get_textures(char *str, t_texture *textures, int i)
{
	str += 2;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (i == NO && !textures->NO)
		textures->NO = ft_strdup(str);
	else if (i == SO && !textures->SO)
		textures->SO = ft_strdup(str);
	else if (i == WE && !textures->WE)
		textures->WE = ft_strdup(str);
	else if (i == EA && !textures->EA)
		textures->EA = ft_strdup(str);
	else
	{
		ft_printf(E_ALREADY_FOUND);
		return (-1);
	}
	if (i == 3)
	{
		if (!textures->NO || !textures->SO || !textures->WE || !textures->EA)
			return (-1);
	}
	return (1);
}

int	init_textures(char **grid, t_game *cube)
{
	t_texture	*textures;
	int			i;
	int			count;

	textures = (t_texture *)ft_calloc(1, sizeof(t_texture));
	i = 0;
	count = 0;
	while (grid[i])
	{
		if (ft_strncmp("NO ", grid[i], 3) == 0 || ft_strncmp("SO ", grid[i],
				3) == 0 || ft_strncmp("EA ", grid[i], 3) == 0
			|| ft_strncmp("WE ", grid[i], 3) == 0 )
		{
			if (get_textures(grid[i], textures, count) < 0)
				return (-1);
			count++;
		}
		i++;
	}
	if (count == TEXTURES_FOUND)
	{
		cube->textures = textures;
		return (0);
	}
	return (-1);
}
static int get_colors(char *str,t_texture *textures, int i)
{
	int j;
	int len;
	char *tmp;

	j = 0;
	len = 0;
	while(*str && *str != '\n')
	{
		if (j > 2)
		{
			ft_printf(E_BAD_COLOR_USAGE);
			return (-1);
		}
		str++;
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		while(*str && *str != '\n' &&*str != ',' )
		{
			len++;
			str++;
		}
		if (len > 3 || len == 0)
		{
			ft_printf(E_BAD_COLOR_USAGE);
			return(-1);
		}
		str -= len;
		if ( i == FLOOR  && !textures->floor[j])
		{
			tmp = ft_strldup(str, len);
			textures->floor[j] = ft_atoi(tmp);
			free(tmp);
			if (&textures->floor[j] == NULL)
				return (-1);
			if (textures->floor[j] > 255)
			{
				ft_printf(E_BAD_COLOR_USAGE);
				return (-1);
			}
		}
		else if ( i == CEILING  && !textures->ceiling[j])
		{
			tmp = ft_strldup(str, len);
			textures->ceiling[j] = ft_atoi(tmp);
			free(tmp);
			if (&textures->ceiling[j] == NULL)
				return (-1);
			if (textures->floor[j] > 255)
			{
				ft_printf(E_BAD_COLOR_USAGE);
				return (-1);
			}
		}
		else
			return (-1);
		str += len;
		len = 0;
		j++;
	}
	if (j == 3)
		return (0);
	return (-1);
}

int init_colors(char **grid, t_game *cube)
{
	int i;
	int count;
	count = 0;
	i = 0;

	while (grid[i])
	{
		if (ft_strncmp("F ", grid[i], 2) == 0 || ft_strncmp("C ", grid[i], 2) == 0)
		{
			if(get_colors(grid[i],cube->textures,count) < 0)
				return(-1);
			count++;
		}
		i++;
	}
	if (count == COLORS_FOUND)
		return(0);
	return(-1);
}
