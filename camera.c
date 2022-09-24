/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:21:19 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/23 15:24:50 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static	void	create_camera_matrix(t_camera *camera, float pos[VEC3_SIZE], \
				float normal[VEC3_SIZE], float v_up[VEC3_SIZE]);

t_camera	*new_camera(float pos[VEC3_SIZE], float ovector[VEC3_SIZE], \
			float fov)
{
	t_camera	*camera;
	float		v_up[VEC3_SIZE];

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
	vec3(0, 1, 0, v_up);
	if (ovector[1] == 1.f || ovector[1] == -1.f)
		vec3(1, 0, 0, v_up);
	create_camera_matrix(camera, pos, ovector, v_up);
	return (camera);
}

static	void	create_camera_matrix(t_camera *camera, float pos[VEC3_SIZE], \
				float normal[VEC3_SIZE], float v_up[VEC3_SIZE])
{
	struct s_mat4	transf;
	float			v[VEC3_SIZE];
	float			u[VEC3_SIZE];

	vec3_cross(normal, v_up, u);
	vec3_cross(u, normal, v);
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
	transf.m44 = 1;
	transf.m41 = 0;
	transf.m42 = 0;
	transf.m43 = 0;
	mat_copy(transf.v, MAT4_SIZE, camera->transform.forward);
	mat4_inverse(camera->transform.forward, camera->transform.backward);
}
