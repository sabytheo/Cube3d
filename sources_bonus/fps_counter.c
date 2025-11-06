/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: optimization                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by optim             #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by optim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include <sys/time.h>


t_fps	*init_fps_counter(void)
{
	t_fps *fps;

	fps = malloc(sizeof(t_fps));
	if (!fps)
		return (NULL);
	fps->frame_count = 0;
	fps->fps = 0.0;
	gettimeofday(&fps->last_fps_update, NULL);
	ft_memset(fps->fps_string, 0, 32);
	return (fps);
}

// Calculer le temps en secondes entre deux timevals
static double	get_time_diff_sec(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) +
		(end->tv_usec - start->tv_usec) / 1000000.0);
}

// Mettre à jour le compteur FPS
void	update_fps_counter(t_game *cube)
{
	struct timeval current_time;
	double elapsed;

	if (!cube->fps_counter)
		return;

	cube->fps_counter->frame_count++;
	gettimeofday(&current_time, NULL);

	// Calculer le temps écoulé depuis la dernière mise à jour
	elapsed = get_time_diff_sec(&cube->fps_counter->last_fps_update,
		&current_time);

	// Mettre à jour les FPS toutes les 0.5 secondes
	if (elapsed >= 0.5)
	{
		cube->fps_counter->fps = cube->fps_counter->frame_count / elapsed;
		cube->fps_counter->frame_count = 0;
		cube->fps_counter->last_fps_update = current_time;

		// Créer la chaîne FPS
		snprintf(cube->fps_counter->fps_string, 32, "FPS: %.1f",
			cube->fps_counter->fps);
	}
}

// Afficher le compteur FPS à l'écran
void	draw_fps_counter(t_game *cube)
{
	if (!cube->fps_counter)
		return;

	// Afficher le texte en haut à gauche
	// Couleur blanche : 0xFFFFFF
	mlx_string_put(cube->mlx, cube->windows, 10, 20, 0x00FFFFFF,
		cube->fps_counter->fps_string);
}

// Version améliorée avec fond noir pour meilleure lisibilité
void	draw_fps_counter_with_bg(t_game *cube)
{
	int i;
	int j;

	if (!cube->fps_counter)
		return;

	// Dessiner un fond noir semi-transparent
	i = 5;
	while (i < 150)
	{
		j = 5;
		while (j < 35)
		{
			img_pixel_put(cube->img, i, j, 0x00000000);
			j++;
		}
		i++;
	}

	// Afficher le texte en blanc
	mlx_string_put(cube->mlx, cube->windows, 10, 20, 0x00FFFFFF,
		cube->fps_counter->fps_string);
}

// Normaliser l'angle entre -180 et 180 degrés
static double	normalize_angle_180(double angle_rad)
{
	double angle_deg;

	angle_deg = angle_rad * 180.0 / M_PI;

	// Ramener entre 0 et 360
	while (angle_deg < 0)
		angle_deg += 360.0;
	while (angle_deg >= 360.0)
		angle_deg -= 360.0;

	// Convertir en -180 à 180
	if (angle_deg > 180.0)
		angle_deg -= 360.0;

	return (angle_deg);
}

// Normaliser l'angle entre 0 et 360 degrés
static double	normalize_angle_360(double angle_rad)
{
	double angle_deg;

	angle_deg = angle_rad * 180.0 / M_PI;

	// Ramener entre 0 et 360
	while (angle_deg < 0)
		angle_deg += 360.0;
	while (angle_deg >= 360.0)
		angle_deg -= 360.0;

	return (angle_deg);
}

// Obtenir la direction cardinale (N, S, E, W, NE, NW, SE, SW)
static const char	*get_cardinal_direction(double angle_rad)
{
	double angle_deg = normalize_angle_360(angle_rad);

	// Nord = 90°, Est = 0°, Sud = 270°, Ouest = 180°
	if (angle_deg >= 67.5 && angle_deg < 112.5)
		return ("N");
	else if (angle_deg >= 22.5 && angle_deg < 67.5)
		return ("NE");
	else if (angle_deg >= 337.5 || angle_deg < 22.5)
		return ("E");
	else if (angle_deg >= 292.5 && angle_deg < 337.5)
		return ("SE");
	else if (angle_deg >= 247.5 && angle_deg < 292.5)
		return ("S");
	else if (angle_deg >= 202.5 && angle_deg < 247.5)
		return ("SW");
	else if (angle_deg >= 157.5 && angle_deg < 202.5)
		return ("W");
	else
		return ("NW");
}

// Version avec infos supplémentaires (position du joueur, angle)
// Mode 1 : angle entre 0 et 360
void	draw_debug_info(t_game *cube)
{
	char pos_str[64];
	char angle_str[64];
	double angle_deg;
	int y_offset;

	if (!cube->fps_counter)
		return;

	y_offset = 20;
	angle_deg = normalize_angle_360(cube->player.angle);

	// Fond noir pour toutes les infos
	int i = 5;
	while (i < 250)
	{
		int j = 5;
		while (j < 85)
		{
			img_pixel_put(cube->img, i, j, 0x00000000);
			j++;
		}
		i++;
	}

	// FPS
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, 0x00FFFFFF,
		cube->fps_counter->fps_string);

	// Position
	y_offset += 20;
	snprintf(pos_str, 64, "Pos: (%.2f, %.2f)",
		cube->player.pos_x, cube->player.pos_y);
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, 0x00FFFF00, pos_str);

	// Angle (0-360°)
	y_offset += 20;
	snprintf(angle_str, 64, "Angle: %.1f deg", angle_deg);
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, 0x00FF00FF,
		angle_str);
}

// Version alternative : angle entre -180 et 180
void	draw_debug_info_180(t_game *cube)
{
	char pos_str[64];
	char angle_str[64];
	double angle_deg;
	int y_offset;

	if (!cube->fps_counter)
		return;

	y_offset = 20;
	angle_deg = normalize_angle_180(cube->player.angle);

	// Fond noir
	int i = 5;
	while (i < 250)
	{
		int j = 5;
		while (j < 85)
		{
			img_pixel_put(cube->img, i, j, 0x00000000);
			j++;
		}
		i++;
	}

	// FPS
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, 0x00FFFFFF,
		cube->fps_counter->fps_string);

	// Position
	y_offset += 20;
	snprintf(pos_str, 64, "Pos: (%.2f, %.2f)",
		cube->player.pos_x, cube->player.pos_y);
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, 0x00FFFF00, pos_str);

	// Angle (-180 à 180°)
	y_offset += 20;
	snprintf(angle_str, 64, "Angle: %.1f deg", angle_deg);
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, 0x00FF00FF,
		angle_str);
}

// Version ultime : avec direction cardinale
void	draw_debug_info_cardinal(t_game *cube)
{
	char pos_str[64];
	char angle_str[80];
	double angle_deg;
	const char *direction;
	int y_offset;

	if (!cube->fps_counter)
		return;

	y_offset = 20;
	angle_deg = normalize_angle_360(cube->player.angle);
	direction = get_cardinal_direction(cube->player.angle);

	// Fond noir
	int i = 5;
	while (i < 280)
	{
		int j = 5;
		while (j < 85)
		{
			img_pixel_put(cube->img, i, j, 0x00000000);
			j++;
		}
		i++;
	}

	// FPS
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, RED,
		cube->fps_counter->fps_string);

	// Position
	y_offset += 20;
	snprintf(pos_str, 64, "Pos: (%.2f, %.2f)",
		cube->player.pos_x, cube->player.pos_y);
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, 0x00FFFF00, pos_str);

	// Angle avec direction cardinale
	y_offset += 20;
	snprintf(angle_str, 80, "Dir: %.1f deg (%s)", angle_deg, direction);
	mlx_string_put(cube->mlx, cube->windows, 10, y_offset, 0x00FF00FF,
		angle_str);
}

// Libérer la mémoire du compteur
void	free_fps_counter(t_fps *fps)
{
	if (fps)
		free(fps);
}
