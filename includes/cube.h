/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/08/08 16:07:17 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "ft_printf.h"
# include "ft_printf_fd.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	BUTTON_PRESS_MASK = 1L << 2,
	W = 119,
	S = 115,
	D = 100,
	A = 97,
	ESCAPE = 65307
};

typedef struct s_gamestruct
{
	int		height;
	int		*width;
	char	**map;
	int 	player_start_x;
	int 	player_start_y;
	int 	player_start_dir;
	float   pos_x;
	float   pos_y;
	double	angle;
	float	fov;
	void	*mlx;
	void	*windows;

}			t_gamestruct;

void	print_map(char **map);
void print_width(t_gamestruct *cube);

int	free_exit(t_gamestruct *cube);
int	parse_map(t_gamestruct *cube, char **argv);

#endif
