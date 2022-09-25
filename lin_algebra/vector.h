/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:48:26 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/01 12:34:15 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdbool.h>
# include <stddef.h> // size_t

# define VEC2_SIZE 2
# define VEC3_SIZE 3
# define VEC4_SIZE 4

struct				s_vec2
{
	union
	{
		struct
		{
			float	x;
			float	y;
		};
		float		v[VEC2_SIZE];
	};
};

struct				s_vec3
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
		};
		float		v[VEC3_SIZE];
	};
};

struct				s_vec4
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
			float	w;
		};
		float		v[VEC4_SIZE];
	};
};

struct				s_quad
{
	float			x;
	float			y;
	float			z;
	float			w;
};

typedef struct s_vec2	t_vec2;
typedef struct s_vec3	t_vec3;
typedef struct s_vec4	t_vec4;

float				*vec_fill(float value, size_t len, float *result);

// vec2 functions

float				*vec2(float x, float y, float *result);
float				*vec2_copy(float *vec, float *result);
float				vec2_length(float *vec);
float				vec2_length_squared(float *vec);
float				*vec2_scalar_mult(float *vec, float s, float *result);
float				*vec2_normalize(float *vec, float *result);
float				*vec2_add(float *v1, float *v2, float *result);
float				*vec2_sub(float *v1, float *v2, float *result);
float				vec2_dot(float *v1, float *v2);
bool				vec2_is_zero(float *vec);
bool				vec2_is_equal(float *v1, float *v2);

float				*vec3(float x, float y, float z, float *result);
float				*vec3_copy(float *vec, float *result);
float				vec3_length(float *vec);
float				vec3_length_squared(float *vec);
float				*vec3_scalar_mult(float *vec, float s, float *result);
float				*vec3_normalize(float *vec, float *result);
float				*vec3_add(float *v1, float *v2, float *result);
float				*vec3_sub(float *v1, float *v2, float *result);
float				vec3_dot(float *v1, float *v2);
float				*vec3_clamp(float *vec, float lower, float upper, \
					float *result);
bool				vec3_is_zero(float *vec);
bool				vec3_is_equal(float *v1, float *v2);
float				*vec3_shift_positive(float *vec, float *result);

float				*vec3_cross(float *v1, float *v2, float *result);

struct s_quad		tuple4(float x, float y, float z, float w);
float				*vec4(struct s_quad values, float *result);
float				*vec4_copy(float *vec, float *result);
float				vec4_length(float *vec);
float				vec4_length_squared(float *vec);
float				*vec4_scalar_mult(float *vec, float s, float *result);
float				*vec4_normalize(float *vec, float *result);
float				*vec4_add(float *v1, float *v2, float *result);
float				*vec4_sub(float *v1, float *v2, float *result);
float				vec4_dot(float *v1, float *v2);
bool				vec4_is_zero(float *vec);
bool				vec4_is_equal(float *v1, float *v2);

void				print_vec2(struct s_vec2 *vec);

#endif
