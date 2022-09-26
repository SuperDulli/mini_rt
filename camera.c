/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:21:19 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/26 14:44:54 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	translate_rotate(pos, ovector, v_up, &camera->transform);
	return (camera);
}
