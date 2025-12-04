/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:42:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/02 17:42:17 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	skip_textures_identifier(char **str)
{
	*str += 2;
	while (**str == ' ' || ((**str >= 9 && **str <= 13) && (**str != '\0')))
		(*str)++;
}

static int	skip_and_copy_path(char **path, char *str)
{
	skip_textures_identifier(&str);
	*path = ft_strdup_no_whitespace(str);
	if (!*path)
		return (-1);
	return (0);
}

static int	cp_mand_textures(char *str, t_textures *textures)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && !textures->no)
		return (skip_and_copy_path(&textures->no, str));
	else if (ft_strncmp(str, "SO ", 3) == 0 && !textures->so)
		return (skip_and_copy_path(&textures->so, str));
	else if (ft_strncmp(str, "WE ", 3) == 0 && !textures->we)
		return (skip_and_copy_path(&textures->we, str));
	else if (ft_strncmp(str, "EA ", 3) == 0 && !textures->ea)
		return (skip_and_copy_path(&textures->ea, str));
	return (-1);
}

int	is_valid_texture(char **grid, int i)
{
	if (ft_strncmp("NO ", grid[i], 3) == 0 || ft_strncmp("SO ", grid[i], 3) == 0
		|| ft_strncmp("EA ", grid[i], 3) == 0 || ft_strncmp("WE ", grid[i],
			3) == 0)
		return (0);
	return (-1);
}

int	init_textures(int *i, char **grid, t_game *cube)
{
	int	count;

	count = 0;
	while (grid[*i])
	{
		if (is_valid_texture(grid, *i) == 0)
		{
			if (cp_mand_textures(grid[*i], &cube->textures) < 0)
				break ;
			count++;
		}
		else if (!is_only_whitespace(i, grid))
			break ;
		(*i)++;
		if (count == TEXTURES_FOUND)
			return (0);
	}
	ft_printf_fd(2, E_PARSING_TEXTURES);
	return (-1);
}
