/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:28:36 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/26 14:38:12 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	set_transform(float transl[VEC3_SIZE], float rotation[VEC3_SIZE], \
		float scale[VEC3_SIZE], t_tform *transform)
{
	float	transl_matrix[MAT4_SIZE];
	float	rotation_x_matrix[MAT4_SIZE];
	float	rotation_y_matrix[MAT4_SIZE];
	float	rotation_z_matrix[MAT4_SIZE];
	float	scale_matrix[MAT4_SIZE];

	mat4_translate(transl[0], transl[1], transl[2], transl_matrix);
	mat4_rotate_x(rotation[0], rotation_x_matrix);
	mat4_rotate_y(rotation[1], rotation_y_matrix);
	mat4_rotate_z(rotation[2], rotation_z_matrix);
	mat4_scale(scale[0], scale[1], scale[2], scale_matrix);
	mat4_mult(transl_matrix, rotation_x_matrix, transform->forward);
	mat4_mult(transform->forward, rotation_y_matrix, transform->forward);
	mat4_mult(transform->forward, rotation_z_matrix, transform->forward);
	mat4_mult(transform->forward, scale_matrix, transform->forward);
	mat4_inverse(transform->forward, transform->backward);
}

float	*apply_transform(float vec[VEC3_SIZE], float transf[MAT4_SIZE], \
		bool is_point, float *result)
{
	float	tmp[VEC4_SIZE];

	if (is_point)
		vec4(tuple4(vec[0], vec[1], vec[2], 1.f), tmp);
	else
		vec4(tuple4(vec[0], vec[1], vec[2], 0.f), tmp);
	mat4_mult_vec4(transf, tmp, tmp);
	vec3(tmp[0], tmp[1], tmp[2], result);
	return (result);
}

void	translate_rotate(float pos[VEC3_SIZE], float normal[VEC3_SIZE],
	float v_up[VEC3_SIZE], t_tform *transform)
{
	struct s_mat4	transf;
	float			v[VEC3_SIZE];
	float			u[VEC3_SIZE];

	vec3_cross(normal, v_up, u);
	vec3_normalize(u, u);
	vec3_cross(u, normal, v);
	vec3_normalize(v, v);
	mat4_identity(transf.v);
	transf.m11 = u[0];
	transf.m21 = u[1];
	transf.m31 = u[2];
	transf.m12 = v[0];
	transf.m22 = v[1];
	transf.m32 = v[2];
	transf.m13 = -normal[0];
	transf.m23 = -normal[1];
	transf.m33 = -normal[2];
	transf.m14 = pos[0];
	transf.m24 = pos[1];
	transf.m34 = pos[2];
	mat_copy(transf.v, MAT4_SIZE, transform->forward);
	mat4_inverse(transform->forward, transform->backward);
}
