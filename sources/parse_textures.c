/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:20:40 by egache            #+#    #+#             */
/*   Updated: 2025/08/28 19:09:51 by tsaby            ###   ########.fr       */
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
int rgb_to_hex(char * line)
{
	int i;

	i = 0;

	while(line[i] != '\n' && line[i])
	{
		while )
	}
}
int	fill_colors(t_game *cube, char *line, int i)
{
	line += 1;
	while (*line == ' ' || *line == '\t')
		line++;

	cube->textures->fc[i] = rgb_to_hex(line);
	if (!cube->textures->fc[i])
	{
		return (-1);
	}
	return (0);
}

int	fill_texture_path(t_game *cube, char *line, int i)
{
	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	cube->textures->wall[i] = ft_strdup(line);
	if (!cube->textures->wall[i])
	{
		return (-1);
	}
	return (0);
}

int find_fc_id(t_game *cube,const char fc_id[2][3], char *line, int i)
{
	ft_printf("%s\n",fc_id[i]);
	if (ft_strncmp(line,fc_id[i], 2) == 0)
		{
			if (!cube->textures->fc[i])
			{
				if (fill_colors(cube, line, i) < 0)
					return (-1);
				return (0);
			}
		}
	return (1);
}

int find_wall_id(t_game *cube,const char wall_id[4][4], char *line, int i)
{
	if (ft_strncmp(line,wall_id[i], 3) == 0)
		{
			if (!cube->textures->wall[i])
			{
				if (fill_texture_path(cube, line, i) < 0)
					return (-1);
				return (0);
			}
		}
	return (1);
}
int	find_identifier(t_game *cube, char *line)
{
	int	i;
	const char wall_id[4][4] = {"NO ","SO ","WE ","EA "};
	const char fc_id[2][3] = {"F ","C "};

	i = 0;
	while (i < 4)
	{
		if(find_wall_id(cube,wall_id,line,i) < 0)
			return (-1);
		if (i < 2)
		{
			if(find_fc_id(cube,fc_id,line,i) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	parse_textures(t_game *cube, char **grid)
{
	int		i;

	i = 0;
	while (grid[i])
	{
		if (find_identifier(cube, grid[i]) < 0)
			return (-1);

		i++;
	}
	return (0);
}
