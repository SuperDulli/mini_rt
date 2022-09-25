/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:18:36 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/19 13:53:20 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

float	mat2_determinant(float *matrix)
{
	struct s_mat2	*m;

	m = (struct s_mat2 *) matrix;
	return (m->m11 * m->m22 - m->m21 * m->m12);
}

float	mat3_determinant(float *matrix)
{
	struct s_mat3	*m;

	m = (struct s_mat3 *) matrix;
	return (m->m11 * m->m22 * m->m33
		+ m->m12 * m->m23 * m->m31
		+ m->m13 * m->m21 * m->m32
		- m->m13 * m->m22 * m->m31
		- m->m12 * m->m21 * m->m33
		- m->m11 * m->m23 * m->m32);
}

float	mat4_determinant(float *matrix)
{
	struct s_mat4	*m;

	m = (struct s_mat4 *) matrix;
	return (
		m->m11 * m->m22 * m->m33 * m->m44 - m->m11 * m->m22 * m->m34 * m->m43
		- m->m11 * m->m23 * m->m32 * m->m44 + m->m11 * m->m23 * m->m34 * m->m42
		+ m->m11 * m->m24 * m->m32 * m->m43 - m->m11 * m->m24 * m->m33 * m->m42
		- m->m12 * m->m21 * m->m33 * m->m44 + m->m12 * m->m21 * m->m34 * m->m43
		+ m->m12 * m->m23 * m->m31 * m->m44 - m->m12 * m->m23 * m->m34 * m->m41
		- m->m12 * m->m24 * m->m31 * m->m43 + m->m12 * m->m24 * m->m33 * m->m41
		+ m->m13 * m->m21 * m->m32 * m->m44 - m->m13 * m->m21 * m->m34 * m->m42
		- m->m13 * m->m22 * m->m31 * m->m44 + m->m13 * m->m22 * m->m34 * m->m41
		+ m->m13 * m->m24 * m->m31 * m->m42 - m->m13 * m->m24 * m->m32 * m->m41
		- m->m14 * m->m21 * m->m32 * m->m43 + m->m14 * m->m21 * m->m33 * m->m42
		+ m->m14 * m->m22 * m->m31 * m->m43 - m->m14 * m->m22 * m->m33 * m->m41
		- m->m14 * m->m23 * m->m31 * m->m42 + m->m14 * m->m23 * m->m32 * m->m41
	);
}
