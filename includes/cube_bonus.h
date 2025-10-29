/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/29 17:37:21 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
#define CUBE_BONUS_H

#include "error.h"
#include "ft_printf.h"
#include "ft_printf_fd.h"
#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

#define _GNU_SOURCE

#define WHITE 0x00FFFFFF
#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define PURPLE 0x00FF00FF

#define WIDTH 1920
#define HEIGHT 1080

// # define SPEED 0.25
# define XBOX 0.2

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
	E = 101,
	F = 102,
	ESCAPE = 65307,
	A_LEFT = 65361,
	A_RIGHT = 65363
};
typedef struct s_vector
{
	float x;
	float y;
} t_vector;

typedef struct s_raycast
{
	float angle;
	float distance;
	float corrected_distance;
	float wall_height;
	int base_height;
	float d_plan;
	float deltaDistY;
	float deltaDistX;
	float sideDistX;
	float sideDistY;
	int stepY;
	int stepX;
	int intX;
	int intY;
	float floatX;
	float floatY;
	t_vector *dir;
} t_raycast;

typedef struct s_player
{
	float pos_x;
	char direction;
	float pos_y;
	double angle;
	float fov;
	float tan_fov_2;
	double speed;
} t_player;

typedef struct s_map
{
	int total_height;
	int max_width;
	int grid_start;
	int grid_height;
	int *width;
	char **grid;
	char **final_grid;
	int start_x;
	int start_y;
	char start_dir;
	bool door_found;

} t_map;

typedef struct s_key
{
	bool w;
	bool s;
	bool a;
	bool d;
	bool e;
	bool f;
	bool left;
	bool right;
	bool escape;

} t_key;

enum direction
{
	NO,
	SO,
	WE,
	EA,
	DO,
	FL,
	CE,
	SP,
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
	void *img_ptr;
	char *addr;
	int bits_per_pixel;
	int size_line;
	int endian;
	int width;
	int height;

} t_img;

typedef struct s_texture
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *DO;
	char *FL;
	char *CE;
	char *SP;
	t_img NO_img;
	t_img SO_img;
	t_img WE_img;
	t_img EA_img;
	t_img DO_img;
	t_img FL_img;
	t_img CE_img;
	t_img SP_img;
	int ceiling[3];
	int floor[3];
	double	y;
	double	x;

} t_texture;

typedef struct s_fps
{
	int frame_count;
	double fps;
	struct timeval last_fps_update;
	char fps_string[32];
}	t_fps;

typedef struct s_hit_info
{
    float distance;
    int side;
    float texture_x;
    char hit_type;
} t_hit_info;

typedef struct s_game
{
	void *mlx;
	void *windows;
	struct timeval last_frame;  // Timer pour limiter les FPS
	int frame_limit;             // Limite en microsecondes (16666 = 60 FPS)
	t_map *map;
	t_img *img;
	t_player *player;
	t_raycast *raycast;
	t_texture textures;
	t_hit_info *hit_info;
	t_fps *fps_counter;
	t_key *key;

} t_game;

void img_pixel_put(t_img *img, int x, int y, int color);
unsigned int	get_texture_pixel(float text_y, t_img *img, float text_x);
t_fps	*init_fps_counter(void);
void	update_fps_counter(t_game *cube);
void	draw_fps_counter(t_game *cube);
void	draw_fps_counter_with_bg(t_game *cube);
void	draw_debug_info(t_game *cube);
void	free_fps_counter(t_fps *fps);
void	draw_debug_info_cardinal(t_game *cube);

// Render
void	render_textured_floor_ceiling(t_game *cube, int x, float draw_start,float draw_end);
void	render_wall(float wall_height, t_game *cube, int x, t_img *img);
void	render(t_game *cube);

// Raycast
void raycast(t_game *cube, t_raycast *raycast);

// Raycast_values
int	init_hit_char(t_game *cube, t_raycast *raycast, t_hit_info **new_hit);
void	init_raycast_direction(t_game *cube, t_raycast *raycast);
void	get_distance_and_wallheight(t_game *cube);
void	init_height_dplan(t_game *cube);
void	init_raycast_values(t_game *cube, t_raycast *raycast, int x);

// Bindings
int define_control(t_game *cube);
int release_key(int keypress, t_game *cube);
int press_key(int keypress, t_game *cube);

// Debug
void print_map(char **map);
void print_width(t_game *cube);
void print_texture(t_texture *textures);

// Reef
int free_exit(t_game *cube);
void free_tab(char **tab);

// Parse_map
int parse_map(t_game *cube, char **argv);

// Parse_grid
int parse_grid(int *i, char **grid, t_game *cube);

// Parse_textures
int init_textures(int *i, char **grid, t_game *cube);

// Parse_colors
int init_colors(int *i, char **grid, t_game *cube);

// Parse_grid_utils
bool is_only_whitespace(int *i, char **grid);
bool is_a_wall(char c);
bool is_a_player(char c);
bool is_a_valid_char(char c, bool state);

// Parse_grid_flood_fill
void flood_fill(int i, int j, t_game *cube);
int vlood_vill(int i, int j, t_game *cube);

#endif
