/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/02 11:12:44 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

# include "error_bonus.h"
# include "ft_printf.h"
# include "ft_printf_fd.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
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
# define MOUSE_SENSIBILITY 0.02
# define XBOX 0.2
# define CHAR_CHECK false
# define GRID_CHECK true
# define ANIMATED_SPRITE 5
# define TEXTURE_EXIST 0

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
	TAB = 65289,
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
	t_img			*texture_assigned;
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
	char			start_dir;
	bool			door_found;

}					t_map;

typedef struct s_minimap
{
	int				mm_width;
	int				player_triangle_size;
	int				vision_range;
	int				tile_width;
	int				tile_height;
	float			player_offset_x;
	float			player_offset_y;
	int				offset_y;
	int				offset_x;
	int				step_x;
	int				step_y;
	int				grid_x;
	int				grid_y;
	int				grid_y_start;
	int				grid_x_start;
	int				depth_offset_x;
	int				depth_offset_y;
	int				grid_y_end;
	int				grid_x_end;
	int				pixel_x;
	int				pixel_y;
	char			c;
	float			center_line_x;
	float			width_offset_x;
	float			center_line_y;
	float			width_offset_y;

}					t_minimap;

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
	bool			tab;
	bool			maj;
}					t_key;

enum				direction
{
	NO,
	SO,
	WE,
	EA,
	DO,
	FL,
	CE,
	SP,
	TEXTURES_FOUND = 13
};

typedef struct s_textures
{
	char			*NO;
	char			*SO[6];
	char			*WE;
	char			*EA;
	char			*DO;
	char			*FL;
	char			*CE;
	char			*CL;
	t_img			NO_img;
	t_img			SO_img[6];
	t_img			WE_img;
	t_img			EA_img;
	t_img			DO_img;
	t_img			FL_img;
	t_img			CE_img;
	t_img			CL_img;
	int				ceiling[3];
	int				floor[3];
	int				current_frame;
	struct timeval	last_frame_time;
	double			y;
	double			x;

}					t_textures;

typedef struct s_hit_info
{
	float			distance;
	int				side;
	float			texture_x;
	char			hit_type;
}					t_hit_info;

typedef struct s_game
{
	void			*mlx;
	void			*windows;
	struct timeval last_frame; // Timer pour limiter les FPS
	long			nb_cores;
	double			delta_time;
	float			last_mouse_pos_x;
	t_map			map;
	t_img			*img;
	t_img			*minimap_img;
	bool			running;
	pthread_mutex_t	running_lock;
	t_minimap		minimap_values;
	t_player		player;
	t_raycast		raycast;
	t_textures		textures;
	t_hit_info		*hit_info;
	t_key			key;
}					t_game;

typedef struct s_cube_thread
{
	t_game			*cube;
	t_raycast		raycast;
	t_hit_info		hit;
	t_map			map;
	t_textures		textures;
	int				width_start;
	int				width_end;
	int				id;
	pthread_t		thread;
}					t_cube_thread;

// Init
void				init_values(t_game *cube);

// Parse_map
int					parse_map(t_game *cube, char **argv);

// Parse_textures
int					init_textures(int *i, char **grid, t_game *cube);

// Parse_textures_utils
int					is_valid_texture(char **grid, int i);

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

// Multithreading
int					launch_threads(t_game *cube, t_cube_thread **cube_thread);
void				free_threads_tab(t_game *cube, t_cube_thread **cube_thread);

// Raycast
void				*raycast(void *arg);

// Raycast_values
void				init_raycast_values(t_game *cube, t_raycast *raycast,
						int x);
void				get_distance_and_wallheight(t_game *cube,
						t_raycast *raycast);
void				init_raycast_direction(t_game *cube, t_raycast *raycast);
int					init_hit_char(t_map *map, t_raycast *raycast,
						t_hit_info **new_hit);

// Render
void				render_wall(float wall_height, t_cube_thread *cube_thread,
						int x, t_raycast *raycast);
void				render(t_game *cube);

// Render_utils
void				img_pixel_put(t_img *img, int x, int y, int color);
unsigned int		get_texture_pixel(float text_y, t_img *img, float text_x);
int					get_color(int red, int green, int blue);

// Render_minimap
void				render_minimap(t_img *minimap, t_game *cube);

// Render_minimap_closed_door
void				draw_closed_door_tile(t_game *cube, t_minimap *mmv);

// Render_minimap_elements
void				draw_minimap_background(t_minimap *mmv, t_img *minimap_img);
void				draw_minimap_player(t_img *minimap_img, t_game *cube,
						t_minimap *mmv);
void				draw_minimap_borders(t_img *minimap_img, int mm_width,
						int tile_width);
void				draw_wall_tile(t_game *cube, t_minimap *mmv);

// Bindings
int					define_control(t_game *cube);

// bindings_utils
void				camera_mouse_control(t_game *cube);
void				update_delta_time(t_game *cube);
int					is_hitting(float x, float y, t_game *cube);
int					press_key(int keypress, t_game *cube);
int					release_key(int keypress, t_game *cube);

// bindings_door
void				open_close_door(t_game *cube);

// Animation
void				update_texture_animation(t_game *cube);

// Free_exit
int					free_exit(t_game *cube);

#endif
