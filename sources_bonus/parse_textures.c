/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:42:42 by tsaby             #+#    #+#             */
/*   Updated: 2026/01/09 13:44:53 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	skip_textures_identifier(char **str)
{
	*str += 2;
	while (**str == ' ' || ((**str >= 9 && **str <= 13) && (**str != '\0')))
		(*str)++;
}

static int	skip_and_copy_path(char **path, char *str)
{
	int	i;

	i = 0;
	skip_textures_identifier(&str);
	while (str && str[i] != '\n' && str[i] != ' ')
		i++;
	if (str[i] == ' ')
	{
		while (str && str[i] == ' ')
			i++;
	}
	if (str[i] != '\n')
		return (-1);
	*path = ft_strdup_no_whitespace(str);
	if (!*path)
		return (-1);
	return (0);
}

static int	cp_mand_textures(char *str, t_textures *textures, int *we_count)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && !textures->no)
		return (skip_and_copy_path(&textures->no, str));
	else if (ft_strncmp(str, "WE ", 3) == 0 && *we_count < 6)
		return (skip_and_copy_path(&textures->we[(*we_count)++], str));
	else if (ft_strncmp(str, "SO ", 3) == 0 && !textures->so)
		return (skip_and_copy_path(&textures->so, str));
	else if (ft_strncmp(str, "EA ", 3) == 0 && !textures->ea)
		return (skip_and_copy_path(&textures->ea, str));
	return (-1);
}

static int	copy_bonus_textures(char *str, t_textures *textures)
{
	if (ft_strncmp(str, "OD ", 3) == 0 && !textures->od)
		return (skip_and_copy_path(&textures->od, str));
	else if (ft_strncmp(str, "FL ", 3) == 0 && !textures->fl)
		return (skip_and_copy_path(&textures->fl, str));
	else if (ft_strncmp(str, "CE ", 3) == 0 && !textures->ce)
		return (skip_and_copy_path(&textures->ce, str));
	else if (ft_strncmp(str, "CD ", 3) == 0 && !textures->cd)
		return (skip_and_copy_path(&textures->cd, str));
	return (-1);
}

int	init_textures(int *i, char **grid, t_game *cube)
{
	int	count;
	int	we_count;

	we_count = 0;
	count = 0;
	while (grid[*i])
	{
		if (is_valid_texture(grid, *i) == 0)
		{
			if (cp_mand_textures(grid[*i], &cube->textures, &we_count) < 0)
			{
				if (copy_bonus_textures(grid[*i], &cube->textures) < 0)
					break ;
			}
			count++;
		}
		else if (!is_only_whitespace(i, grid))
			break ;
		(*i)++;
		if (count == TEXTURES_FOUND)
			return (0);
	}
	ft_printf_fd(2, E_BAD_TEXT_PARSING, grid[*i]);
	return (-1);
}
