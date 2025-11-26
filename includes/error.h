/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:18:37 by tsaby             #+#    #+#             */
/*   Updated: 2025/11/26 13:23:00 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define E_WRONG_EXT "Error :\nFile extension must be .cub\n"
# define E_EMPTY_FILE "Error :\nEmpty file\n"
# define E_WRONG_PATH "Error :\nWrong path for texture.\n"
# define E_BAD_FD "Error :\nOpen failed\n"
# define E_MISSING_PLAYER "Error:\nMissing player char\n"
# define E_MISSING_TEXTURE "Error :\nOne or multiple textures is missing\n"
# define E_MISSING_COLOR "Error :\nOne or multiple colors is missing\n"
# define E_BAD_COLOR_USAGE "Error :\nEmpty field or bad format. Enter 3 values between 0 and 255\n"
# define E_BAD_CHAR_PARSING "Error :\nWrong grid character : %c\n"
# define E_BAD_GRID_PARSING "Error :\nMap should be surrounded by walls\n"
# define E_BAD_GRID_MISSING "Error :\nMap missing\n"
# define E_BAD_MAP_SIZE "Error :\nMap too long\n"

#endif
