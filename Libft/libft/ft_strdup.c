/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:05:21 by tsaby             #+#    #+#             */
/*   Updated: 2025/10/15 18:38:53 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	dest = (char *)malloc((srclen + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	if (!src)
	{
		dest[i] = '\0';
		return (dest);
	}
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
