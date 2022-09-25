/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:30:26 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/08 16:55:15 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

float	*mat4_mult(float *m1, float *m2, float *result)
{
	size_t			i;
	size_t			j;
	size_t			r;
	const size_t	dim = 4;
	float			tmp[MAT4_SIZE];

	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			r = 0;
			tmp[j * dim + i] = 0;
			while (r < dim)
			{
				tmp[j * dim + i] += m1[r * dim + i] * m2[j * dim + r];
				r++;
			}
			j++;
		}
		i++;
	}
	return (mat_copy(tmp, MAT4_SIZE, result));
}

/**
 * @brief matrix vector product - result = matrix * vector
 *
 * @param m matrix
 * @param vec vector
 * @param result
 * @return float[4] result
 */
float	*mat4_mult_vec4(float *m, float *vec, float *result)
{
	size_t			i;
	size_t			j;
	const size_t	dim = 4;
	float			tmp[VEC4_SIZE];

	vec_fill(0, 4, tmp);
	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			tmp[i] = tmp[i] + m[j * dim + i] * vec[j];
			j++;
		}
		i++;
	}
	result[0] = tmp[0];
	result[1] = tmp[1];
	result[2] = tmp[2];
	result[3] = tmp[3];
	return (result);
}
