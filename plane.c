/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:40:03 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/07 14:44:26 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief tests where the ray hits the plane
 *
 * t = ((plane.pos - ray.origin) * plane.normal) / (ray.dir * plane.normal)
 *
 * @param ray
 * @param plane
 * @return float the closest hit point, or -1 if it missed the plane
 */

bool	hit_plane(struct s_ray ray, t_obj *plane, float point[VEC3_SIZE], \
		float local_normal[VEC3_SIZE])
{
	float	numerator;
	float	denominator;
	float	*normal;
	float	tmp[VEC3_SIZE];

	normal = ((t_plane *) plane->specifics)->ovector;
	denominator = vec3_dot(ray.direction, normal);
	if (denominator == 0.f)
		return (false);
	numerator = vec3_dot(vec3_sub(plane->pos, ray.origin, tmp), normal);
	if (numerator / denominator < 0)
		return (false);
	ray_at(&ray, numerator / denominator, point);
	vec3_normalize(ray.direction, ray.direction);
	if (0 <= vec3_dot(normal, ray.direction) && vec3_dot(normal, ray.direction) \
		<= 1)
		vec3_scalar_mult(normal, -1, local_normal);
	else
		vec3_copy(normal, local_normal);
	return (true);
}

/**
 * @brief allocates a new plane object on the heap and initializes it
 *
 * @param pos
 * @param color
 * @param orientation normalized (len == 1)
 * @return t_obj*
 */

t_obj	*new_plane(float pos[VEC3_SIZE], float color[VEC3_SIZE], \
		float orientation[VEC3_SIZE])
{
	t_obj	*obj;
	t_plane	*plane;
	float	transl[VEC3_SIZE];
	float	rot[VEC3_SIZE];
	float	scale[VEC3_SIZE];

	obj = new_object(pos, color);
	if (!obj)
		return (NULL);
	obj->specifics = new(sizeof(t_plane));
	if (!obj->specifics)
	{
		destroy_object(obj);
		return (NULL);
	}
	obj->type = PLANE;
	plane = (t_plane *) obj->specifics;
	vec3_copy(orientation, plane->ovector);
	vec3(pos[0], pos[1], pos[2], transl);
	vec3(0, 0, 0, rot);
	vec3(1.f, 1.f, 1.f, scale);
	set_transform(transl, rot, scale, &obj->transform);
	return (obj);
}

// destroy plane()
//	free(plane);
