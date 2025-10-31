/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:39:56 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/31 13:14:54 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->sl + x * (img->bpp / 8));
	while (i > 0)
	{
		if (img->en != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
unsigned int	get_texture_pixel(float text_y, t_img *img, float text_x)
{
	return (*(unsigned int *)(img->addr + ((int)text_y * img->sl
				+ ((int)(text_x * img->ht)) * (img->bpp / 8))));
}
