/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:03:17 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/16 15:08:01 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

float	*mat_add(float *a, float *b, size_t size, float *result)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		result[i] = a[i] + b[i];
		i++;
	}
	return (result);
}

float	*mat4_add(float *a, float *b, float *result)
{
	return (mat_add(a, b, MAT4_SIZE, result));
}
