/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:28:36 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/21 19:18:29 by chelmerd         ###   ########.fr       */
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

float	*rot_vec_from_orientation(float *orientation, float *result)
{
	float		tmp[VEC3_SIZE];
	float		x_rot;
	float		y_rot;
	float		z_rot;

	x_rot = acosf(vec3_dot(orientation, vec3(1, 0, 0, tmp)));
	y_rot = acosf(vec3_dot(orientation, vec3(0, 1, 0, tmp)));
	z_rot = acosf(vec3_dot(orientation, vec3(0, 0, 1, tmp)));
	vec3(x_rot, y_rot, z_rot, result);
	return (result);
}
