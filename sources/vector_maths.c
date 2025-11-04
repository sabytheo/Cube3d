/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:08:25 by teatime           #+#    #+#             */
/*   Updated: 2025/11/04 15:32:03 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_vector	*vector_normalization(t_vector *vector)
{
	float		vector_norme;
	float		inversed_norme;
	t_vector	*normalized_vector;

	vector_norme = sqrt(pow(vector->x, 2) + pow(vector->y, 2));
	inversed_norme = 1 / vector_norme;
	normalized_vector = malloc(sizeof(t_vector));
	if (!normalized_vector)
		return (NULL);
	normalized_vector->x = vector->x * inversed_norme;
	normalized_vector->y = vector->y * inversed_norme;
	return (normalized_vector);
}
