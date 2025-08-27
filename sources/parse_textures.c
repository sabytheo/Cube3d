/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:20:40 by egache            #+#    #+#             */
/*   Updated: 2025/08/27 19:42:18 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
RGB to HEX :
	- 255 -> FF (for red)
	- 255 -> FF (for green)
	- 0   -> 00 (for blue)
Convert each color to his hex value. Join 3 values and you got hex value

Donc :
- Stocke dans un char** RGB : [255] [255] [0]
- Parsing :
	- Supprimer tous les whitespaces, et la virgule
	- Si autre que whitespaces ou virgule -> ERROR
	- Check que la valeur <= 255
*/

int find_identifier(t_game *cube, char *line)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(line, cube->textures->wall[i][0], 3) == 0)
			if (!cube->textures->wall[i][1])
			{
				fill_texture_path(cube, line, i);
				return (0);
			}
			else
				return (1); // ALREADY FOUND

	}
}

int	fill_texture_path(t_game *cube, char *line, int i)
{
	char *str;

	// FILL LE TAB EN ENLEVANT IDENTIFIER ET LES WHITESPACES ETC ....
	if (ft_strnstr(line, "NO", 2))
	{
		if (cube->textures->no_found == false && str != NULL)
		{
			cube->textures->no_found = true;
			return (1)
		}
		else
			return (0);
	}
}

void	parse_textures(t_game *cube)
{
	char **grid;
	int	i;
	int	j;

	cube->textures->no_found = false;
	grid = cube->map->grid;
	i = 0;
	j = 0;
	while (grid[i])
	{
		if ()
	}
}
