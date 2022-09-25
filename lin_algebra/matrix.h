/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:46:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 15:46:20 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# define _USE_MATH_DEFINES
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include "vector.h"

# define MAT2_SIZE 4
# define MAT3_SIZE 9
# define MAT4_SIZE 16

/*
Matrix 2x2 representation:
0/m11 2/m12
1/m21 3/m22
*/
struct				s_mat2
{
	union
	{
		struct
		{
			float	m11;
			float	m21;
			float	m12;
			float	m22;
		};
		float		v[MAT2_SIZE];
	};
};

/*
Matrix 3x3 representation:
0/m11 3/m12 6/m13
1/m21 4/m22 7/m23
2/m31 5/m32 8/m33
*/
struct				s_mat3
{
	union
	{
		struct
		{
			float	m11;
			float	m21;
			float	m31;
			float	m12;
			float	m22;
			float	m32;
			float	m13;
			float	m23;
			float	m33;
		};
		float		v[MAT3_SIZE];
	};
};

/*
Matrix 4×4 representation:
0/m11 4/m12  8/m13 12/m14
1/m21 5/m22  9/m23 13/m24
2/m31 6/m32 10/m33 14/m34
3/m41 7/m42 11/m43 15/m44
*/
struct				s_mat4
{
	union
	{
		struct
		{
			float	m11;
			float	m21;
			float	m31;
			float	m41;
			float	m12;
			float	m22;
			float	m32;
			float	m42;
			float	m13;
			float	m23;
			float	m33;
			float	m43;
			float	m14;
			float	m24;
			float	m34;
			float	m44;
		};
		float		v[MAT4_SIZE];
	};
};

float				*mat_copy(float *m, size_t size, float *result);
float				*mat_add(float *a, float *b, size_t size, float *result);

float				mat2_determinant(float *matrix);
float				mat3_determinant(float *matrix);
float				mat4_determinant(float *matrix);

float				*mat2_inverse(float *m, float *result);
float				*mat3_inverse(float *m, float *result);
float				*mat4_inverse(float *m, float *result);

float				*mat4_scale(float x, float y, float z, float *result);

float				*mat4_translate(float x, float y, float z, float *result);

float				*mat4_rotate_x(float angle, float *result);
float				*mat4_rotate_y(float angle, float *result);
float				*mat4_rotate_z(float angle, float *result);

float				*mat4_zero(float *result);
float				*mat4_identity(float *result);
float				*mat4_add(float *a, float *b, float *result);
float				*mat_transpose(float *m, size_t dim, float *result);
float				*mat4_mult(float *m1, float *m2, float *result);
float				*mat4_scalar_mult(float *m, float s, float *result);

// matrix vector product

float				*mat4_mult_vec4(float *m, float *vec, float *result);

#endif
