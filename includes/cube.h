/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/27 18:43:57 by egache           ###   ########.fr       */
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
# include <sys/time.h>

# define _GNU_SOURCE
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define PURPLE 0x00FF00FF
# define WIDTH 1920
# define HEIGHT 1080
# define XBOX 0.2
# define DEG_TO_RAD (1.0 / 180.0) * M_PI
# define TEXTURE_EXIST 0
# define CHAR_CHECK false
# define GRID_CHECK true

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
	E = 101,
	F = 102,
	MAJ = 65505,
	ESCAPE = 65307,
	A_LEFT = 65361,
	A_RIGHT = 65363
};

typedef struct s_vector
{
	float			x;
	float			y;
}					t_vector;

typedef struct s_raycast
{
	float			angle;
	float			distance;
	float			corrected_distance;
	float			wall_height;
	int				base_height;
	float			d_plan;
	float			deltaDistY;
	float			deltaDistX;
	float			sideDistX;
	float			sideDistY;
	int				stepY;
	int				stepX;
	int				intX;
	int				intY;
	float			floatX;
	float			floatY;
	float			start_y;
	t_vector		dir;
}					t_raycast;

typedef struct s_player
{
	bool			found;
	float			pos_x;
	char			direction;
	float			pos_y;
	double			angle;
	float			fov;
	float			tan_fov_2;
	double			speed;
	double			rotation_speed;
}					t_player;

typedef struct s_map
{
	int				total_height;
	int				grid_start;
	int				grid_height;
	int				*width;
	char			**grid;
	char			**final_grid;
	int				start_x;
	int				start_y;
	char			start_dir;
}					t_map;

typedef struct s_key
{
	bool			w;
	bool			s;
	bool			a;
	bool			d;
	bool			e;
	bool			f;
	bool			left;
	bool			right;
	bool			escape;
	bool			maj;
}					t_key;

enum				direction
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
	void			*img;
	char			*addr;
	int				bpp;
	int				sl;
	int				en;
	int				wh;
	int				ht;
}					t_img;

typedef struct s_textures
{
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	t_img			NO_img;
	t_img			SO_img;
	t_img			WE_img;
	t_img			EA_img;
	int				ceiling[3];
	int				floor[3];
	double			y;
	double			x;

}					t_textures;

typedef struct s_game
{
	void			*mlx;
	void			*windows;
	double			delta_time;
	struct timeval 	last_frame; // Timer pour limiter les FPS
	int 			frame_limit;           // Limite en microsecondes (16666 = 60 FPS)
	t_map			map;
	t_img			*img;
	t_player		player;
	t_raycast		raycast;
	t_textures		textures;;
	t_key			key;

}					t_game;

// Init
void	init_values(t_game *cube);

// Parse_map
int					parse_map(t_game *cube, char **argv);

// Parse_map_utils
int					copy_line(t_game *cube, char *line);
int					init_textures_then_colors(t_game *cube, int *i,
						char **grid);
int					init_colors_then_textures(t_game *cube, int *i,
						char **grid);

// Parse_textures
int					init_textures(int *i, char **grid, t_game *cube);
int					is_valid_texture(char **grid, int i);

// Parse_colors
int					init_colors(int *i, char **grid, t_game *cube);

// Parse_colors_utils
int					str_is_digit(char *str);
int					check_len_and_skip_space(char **str, int *j, int *len);

// Parse_grid
int					parse_grid(int *i, char **grid, t_game *cube);

// Parse_grid_utils
int					get_width(char **map, t_game *cube, int i);
void				get_angle(t_game *cube, char c);
bool				is_only_whitespace(int *i, char **grid);
bool				is_a_player(char c);
bool				is_a_valid_char(t_game *cube, char c, bool state);

// Parse_grid_flood_fill
int					flood_fill(int i, int j, t_game *cube);

// Load_textures
int					load_textures(t_game *cube, t_textures *textures);

// Raycast
void				raycast(t_game *cube, t_raycast *raycast);

// Raycast_value
void				init_raycast_values(t_game *cube, t_raycast *raycast,
						int x);
void				init_raycast_direction(t_game *cube, t_raycast *raycast);
void				get_distance_and_wallheight(t_game *cube,
						t_raycast *raycast, int side);

// Render
void				render(t_game *cube);
void				render_wall(float wall_height, t_game *cube, int x,
						t_img *texture);

// Render_utils
unsigned int		get_texture_pixel(float text_y, t_img *img, float text_x);
void				img_pixel_put(t_img *img, int x, int y, int color);
int					get_color(int red, int green, int blue);

// Bindings
int					define_control(t_game *cube);

// Bindings_utils
void				update_delta_time(t_game *cube);
int					is_hitting(float x, float y, t_game *cube);
int					release_key(int keypress, t_game *cube);
int					press_key(int keypress, t_game *cube);

// Free_exit
int					free_exit(t_game *cube);

#endif
