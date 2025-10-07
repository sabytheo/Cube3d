/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:29:30 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/07 13:31:20 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_len_and_skip_space(char **str, int *j, int *len)
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

int	get_ceiling_values(char **str, int *len, t_texture *textures)
{
	char	*tmp;
	int		j;

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

int	get_floor_values(char **str, int *len, t_texture *textures)
{
	char	*tmp;
	int		j;

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

static int	get_colors(char *str, t_texture *textures)
{
	int	len;

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

int	init_colors(int *i, char **grid, t_game *cube)
{
	int	count;

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
