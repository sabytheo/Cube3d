/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:18:37 by tsaby             #+#    #+#             */
/*   Updated: 2025/12/11 15:56:28 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define E_WRONG_INIT "Error\nUse valid window or hitbox values\n"
# define E_WRONG_EXT "Error\nFile extension must be .cub\n"
# define E_EMPTY_FILE "Error\nEmpty file\n"
# define E_WRONG_PATH "Error\nUnexpected path for texture\n"
# define E_BAD_FD "Error\nOpen failed\n"
# define E_MISSING_PLAYER "Error\nMissing player character\n"
# define E_BAD_COLOR_USAGE "Error\nEmpty field or bad format\n\
Enter 3 values between 0 and 255\n"
# define E_BEFORE_PARSING "Error\nUnexpected line : %s\
2 colors are expected\n1 of each : [\"C \" \"F \"]\n\
4 textures are expected\n1 of each : [\"NO \" \"SO \" \"WE \" \"EA \"]\n"
# define E_BAD_TEXT_PARSING "Error\nUnexpected line : %s\
4 textures are expected\n1 of each : [\"NO \" \"SO \" \"WE \" \"EA \"]\n"
# define E_BAD_COLOR_PARSING "Error\nUnexpected line : %s\
2 colors are expected\n1 of each : [\"C \" \"F \"]\n"
# define E_BAD_CHAR_PARSING "Error\nUnexpected grid character : %c\n"
# define E_BAD_GRID_PARSING "Error\nMap should be surrounded by walls\n"
# define E_BAD_GRID_MISSING "Error\nMap missing\n"
# define E_BAD_MAP_SIZE "Error\nMap too long\n"

#endif
