/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:21:19 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/22 11:04:40 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_camera	*new_camera(float pos[VEC3_SIZE], float ovector[VEC3_SIZE], float fov)
{
	t_camera	*camera;
	float		transl_matrix[MAT4_SIZE];
	struct		s_mat4 transf;
	float		v_up[VEC3_SIZE]; // where is up in the world
	float		v[VEC3_SIZE]; // camera vertical
	float		normal[VEC3_SIZE]; // view plane normal, i. e. camera orientation
	float		u[VEC3_SIZE]; // right

	camera = new(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->pos[0] = pos[0];
	camera->pos[1] = pos[1];
	camera->pos[2] = pos[2];
	vec3_normalize(ovector, ovector);
	camera->ovector[0] = ovector[0];
	camera->ovector[1] = ovector[1];
	camera->ovector[2] = ovector[2];
	camera->fov = fov;

	vec3(0,1,0, v_up);
	vec3_copy(ovector, normal);
	// cross product of parrallel vectors is not helpfull
	if (normal[1] == 1.f || normal[1] == -1.f)
		vec3(1,0,0, v_up);

	// init v, n, u
	vec3_cross(v_up, normal, u);
	vec3_cross(normal, u, v);

	transf.m11 = u[0];
	transf.m21 = u[1];
	transf.m31 = u[2];
	transf.m12 = v[0];
	transf.m22 = v[1];
	transf.m32 = v[2];
	transf.m13 = -normal[0];
	transf.m23 = -normal[1];
	transf.m33 = -normal[2];

	transf.m14 = 0;
	transf.m24 = 0;
	transf.m34 = 0;
	transf.m44 = 1;
	transf.m41 = 0;
	transf.m42 = 0;
	transf.m43 = 0;

	mat4_translate(pos[0], pos[1], pos[2], transl_matrix);
	mat4_mult(transf.v, transl_matrix, transf.v);
	mat_copy(transf.v, MAT4_SIZE, camera->transform.forward);
	mat4_inverse(camera->transform.forward, camera->transform.backward);

	return (camera);
}
