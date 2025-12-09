/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:42:11 by egache            #+#    #+#             */
/*   Updated: 2025/12/09 17:51:05 by egache           ###   ########.fr       */
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
			ft_printf_fd(2, "Error\nEnter only digits values\n");
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
		ft_printf_fd(2, "Erro\nEnter a 3 digit value\n");
		return (-1);
	}
	(*str)++;
	if (*j == 0)
	{
		while (**str == ' ' || (**str >= 9 && **str <= 13))
			(*str)++;
	}
	while (**str && **str != '\n' && **str != ',')
	{
		(*len)++;
		(*str)++;
	}
	if (*len > 3 || *len == 0)
	{
		ft_printf_fd(2, "Error\nOne or multiple RGB value missing\n");
		return (-1);
	}
	(*str) -= (*len);
	return (0);
}
