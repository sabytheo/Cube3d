/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/09/29 17:16:19 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "error.h"
# include "ft_printf.h"
# include "ft_printf_fd.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define PURPLE 0x00FF00FF

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

typedef struct s_player
{
	float		pos_x;
	char		direction;
	float		pos_y;
	double		angle;
	float		fov;
}				t_player;

typedef struct s_map
{
	int			total_height;
	int			max_width;
	int			grid_start;
	int			grid_height;
	int			*width;
	char		**grid;
	char		**final_grid;
	int			start_x;
	int			start_y;
	char		start_dir;

}				t_map;

typedef struct s_texture
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	int			ceiling[3];
	int			floor[3];

}				t_texture;

enum			direction
{
	NO,
	SO,
	WE,
	EA,
	TEXTURES_FOUND
};

enum
{
	FLOOR,
	CEILING,
	COLORS_FOUND
};

typedef struct s_game
{
	void		*mlx;
	void		*windows;
	t_map		*map;
	t_player	*player;
	t_texture	*textures;

}				t_game;

int				init_textures(int *i, char **grid, t_game *cube);
int				init_colors(int *i, char **grid, t_game *cube);

// Debug
void			print_map(char **map);
void			print_width(t_game *cube);
void			print_texture(t_texture *textures);

// Reef
int				free_exit(t_game *cube);

// Parse_map
int				parse_map(t_game *cube, char **argv);

// Parse_grid
void parse_grid(int *i, char **grid, t_game *cube);

#endif
