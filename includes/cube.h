/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/08 19:11:02 by egache           ###   ########.fr       */
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
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

#define _GNU_SOURCE

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define PURPLE 0x00FF00FF

# define WIDTH 640
# define HEIGHT 480

# define BEFORE_FF false
# define AFTER_FF true

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

typedef struct s_vector
{
	float		x;
	float		y;
}				t_vector;

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

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;

}				t_img;

typedef struct s_game
{
	void		*mlx;
	void		*windows;
	t_map		*map;
	t_img		*img;
	t_player	*player;
	t_texture	*textures;

}				t_game;

void			render(t_game *cube);

// Debug
void			print_map(char **map);
void			print_width(t_game *cube);
void			print_texture(t_texture *textures);

// Reef
int				free_exit(t_game *cube);
void			free_tab(char **tab);

// Parse_map
int				parse_map(t_game *cube, char **argv);

// Parse_grid
int				parse_grid(int *i, char **grid, t_game *cube);

// Parse_textures
int				init_textures(int *i, char **grid, t_game *cube);

// Parse_colors
int				init_colors(int *i, char **grid, t_game *cube);

// Parse_grid_utils
bool			is_only_whitespace(int *i, char **grid);
bool			is_a_wall(char c);
bool			is_a_player(char c);
bool			is_a_valid_char(char c, bool state);

// Parse_grid_flood_fill
void			flood_fill(int i, int j, t_game *cube);
int				vlood_vill(int i, int j, t_game *cube);

#endif
