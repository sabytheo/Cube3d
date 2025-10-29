/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:39:56 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/29 17:35:44 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bits_per_pixel - 8;
	pixel = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	while (i > 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bits_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}
unsigned int	get_texture_pixel(float text_y, t_img *img, float text_x)
{
	return (*(unsigned int *)(img->addr + ((int)text_y * img->size_line
				+ ((int)(text_x * img->height)) * (img->bits_per_pixel / 8))));
}
