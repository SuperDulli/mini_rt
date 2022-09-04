/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:21:19 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/04 16:17:56 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_camera	*new_camera(float pos[VEC3_SIZE], float ovector[VEC3_SIZE], float fov)
{
	t_camera	*camera;

	camera = new(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->pos[0] = pos[0];
	camera->pos[1] = pos[1];
	camera->pos[2] = pos[2];
	camera->ovector[0] = ovector[0];
	camera->ovector[1] = ovector[1];
	camera->ovector[2] = ovector[2];
	camera->fov = fov;
	return (camera);
}
