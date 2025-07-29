/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/29 21:14:17 by tsaby            ###   ########.fr       */
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
	int		fd;
	int		hmap;
	char	**map;
	void	*mlx;
	void	*windows;

}			t_gamestruct;

void	print_map(char **map);
int	free_exit(t_gamestruct *cube);
int	init_map(t_gamestruct *cube, char **argv);

#endif
