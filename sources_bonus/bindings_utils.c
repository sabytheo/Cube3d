/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:28:58 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:23:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	is_hitting(float x, float y, t_game *cube)
{
	static const char	c[2] = {'1', 'C'};

	if (cube->map.final_grid[(int)(y + XBOX)][(int)(x + XBOX)] != c[0]
		&& cube->map.final_grid[(int)(y + XBOX)][(int)(x + XBOX)] != c[1])
	{
		if (cube->map.final_grid[(int)(y + XBOX)][(int)(x - XBOX)] != c[0]
			&& cube->map.final_grid[(int)(y + XBOX)][(int)(x - XBOX)] != c[1])
		{
			if (cube->map.final_grid[(int)(y - XBOX)][(int)(x + XBOX)] != c[0]
				&& cube->map.final_grid[(int)(y - XBOX)][(int)(x
					+ XBOX)] != c[1])
			{
				if (cube->map.final_grid[(int)(y - XBOX)][(int)(x
						- XBOX)] != c[0] && cube->map.final_grid[(int)(y
						- XBOX)][(int)(x - XBOX)] != c[1])
				{
					return (0);
				}
				return (-1);
			}
			return (-1);
		}
		return (-1);
	}
	return (-1);
}

int	press_key(int keypress, t_game *cube)
{
	if (keypress == W)
		cube->key->w = true;
	if (keypress == S)
		cube->key->s = true;
	if (keypress == A)
		cube->key->a = true;
	if (keypress == D)
		cube->key->d = true;
	if (keypress == E)
		cube->key->e = true;
	if (keypress == F)
		cube->key->f = true;
	if (keypress == A_LEFT)
		cube->key->left = true;
	if (keypress == A_RIGHT)
		cube->key->right = true;
	if (keypress == ESCAPE)
		cube->key->escape = true;
	return (0);
}

int	release_key(int keypress, t_game *cube)
{
	if (keypress == W)
		cube->key->w = false;
	if (keypress == S)
		cube->key->s = false;
	if (keypress == A)
		cube->key->a = false;
	if (keypress == D)
		cube->key->d = false;
	if (keypress == E)
		cube->key->e = false;
	if (keypress == F)
		cube->key->f = false;
	if (keypress == A_LEFT)
		cube->key->left = false;
	if (keypress == A_RIGHT)
		cube->key->right = false;
	if (keypress == ESCAPE)
		cube->key->escape = false;
	return (0);
}
