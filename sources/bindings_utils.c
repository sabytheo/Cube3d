/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:11:35 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/06 15:21:18 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_hitting(float x, float y, t_game *cube, char c)
{
	if (cube->map.final_grid[(int)(y + XBOX)][(int)(x + XBOX)] != c)
	{
		if (cube->map.final_grid[(int)(y + XBOX)][(int)(x - XBOX)] != c)
		{
			if (cube->map.final_grid[(int)(y - XBOX)][(int)(x + XBOX)] != c)
			{
				if (cube->map.final_grid[(int)(y - XBOX)][(int)(x
						- XBOX)] != c)
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
