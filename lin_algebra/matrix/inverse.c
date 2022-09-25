/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:22:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/20 12:10:24 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

float	*mat2_inverse(float *m, float *result)
{
	const float	determinant = mat2_determinant(m);
	float		tmp[MAT2_SIZE];

	if (!determinant)
		return (m);
	tmp[0] = (1 / determinant) * m[3];
	tmp[1] = (1 / determinant) * -m[2];
	tmp[2] = (1 / determinant) * -m[1];
	tmp[3] = (1 / determinant) * m[0];
	result[0] = tmp[0];
	result[1] = tmp[1];
	result[2] = tmp[2];
	result[3] = tmp[3];
	return (result);
}

float	*mat3_inverse(float *m, float *result)
{
	const float	determinant = mat3_determinant(m);
	float		tmp[MAT3_SIZE];

	if (!determinant)
		return (m);
	tmp[0] = (1 / determinant) * (m[4] * m[8] - m[7] * m[5]);
	tmp[1] = (1 / determinant) * (m[7] * m[2] - m[1] * m[8]);
	tmp[2] = (1 / determinant) * (m[1] * m[5] - m[4] * m[2]);
	tmp[3] = (1 / determinant) * (m[6] * m[5] - m[3] * m[8]);
	tmp[4] = (1 / determinant) * (m[0] * m[8] - m[6] * m[2]);
	tmp[5] = (1 / determinant) * (m[3] * m[2] - m[0] * m[5]);
	tmp[6] = (1 / determinant) * (m[3] * m[7] - m[6] * m[4]);
	tmp[7] = (1 / determinant) * (m[6] * m[1] - m[0] * m[7]);
	tmp[8] = (1 / determinant) * (m[0] * m[4] - m[3] * m[1]);
	return (mat_copy(tmp, MAT3_SIZE, result));
}

// norm https://stackoverflow.com/a/1148405
float	*mat4_prepare_invert(float *m, float *tmp)
{
	tmp[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] \
			+ m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	tmp[1] = m[1] * m[11] * m[14] - m[1] * m[10] * m[15] + m[9] * m[2] * m[15] \
			- m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	tmp[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + \
			m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
	tmp[3] = m[1] * m[7] * m[10] - m[1] * m[6] * m[11] + m[5] * m[2] * m[11] - \
			m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
	tmp[4] = m[4] * m[11] * m[14] - m[4] * m[10] * m[15] + m[8] * m[6] * m[15] \
			- m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	tmp[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] \
			+ m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	tmp[6] = m[0] * m[7] * m[14] - m[0] * m[6] * m[15] + m[4] * m[2] * m[15] - \
			m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
	tmp[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + \
			m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
	tmp[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + \
			m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
	tmp[9] = m[0] * m[11] * m[13] - m[0] * m[9] * m[15] + m[8] * m[1] * m[15] - \
			m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
	return (tmp);
}

float	*mat4_inverse(float *m, float *result)
{
	const float	determinant = mat4_determinant(m);
	float		tmp[MAT4_SIZE];

	if (!determinant)
		return (m);
	mat4_prepare_invert(m, tmp);
	tmp[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + \
			m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
	tmp[11] = m[0] * m[7] * m[9] - m[0] * m[5] * m[11] + m[4] * m[1] * m[11] - \
			m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
	tmp[12] = m[4] * m[10] * m[13] - m[4] * m[9] * m[14] + m[8] * m[5] * m[14] \
			- m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
	tmp[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] \
			+ m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
	tmp[14] = m[0] * m[6] * m[13] - m[0] * m[5] * m[14] + m[4] * m[1] * m[14] - \
			m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
	tmp[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + \
			m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
	return (mat4_scalar_mult(tmp, 1 / determinant, result));
}
