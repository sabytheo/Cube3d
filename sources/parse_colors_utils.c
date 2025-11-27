/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:42:11 by egache            #+#    #+#             */
/*   Updated: 2025/11/27 15:48:03 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf_fd(2, E_BAD_COLOR_USAGE);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_len_and_skip_space(char **str, int *j, int *len)
{
	if (*j > 2)
	{
		ft_printf_fd(2, E_BAD_COLOR_USAGE);
		return (-1);
	}
	(*str)++;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	while (**str && **str != '\n' && **str != ',')
	{
		(*len)++;
		(*str)++;
	}
	if (*len > 3 || *len == 0)
	{
		ft_printf_fd(2, E_BAD_COLOR_USAGE);
		return (-1);
	}
	(*str) -= (*len);
	return (0);
}
