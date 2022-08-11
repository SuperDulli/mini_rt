/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:40:03 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/10 19:02:03 by chelmerd         ###   ########.fr       */
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
float	hit_plane(struct s_ray *ray, t_obj *plane)
{
	float	numerator;
	float	denominator;
	float	*normal;
	float	tmp[VEC3_SIZE];

	normal = ((t_plane *) plane->specifics)->ovector;

	// apply_transform(ray->direction, plane->transform.backward, 0, ray->direction);
	// apply_transform(ray->origin, plane->transform.backward, 1, ray->origin);
	denominator = vec3_dot(ray->direction, normal);
	if (denominator == 0.f)
		return (0.f); // ray is parallel to plane
	numerator = vec3_dot(vec3_sub(plane->pos, ray->origin, tmp), normal);

	return (numerator / denominator);
}

/**
 * @brief allocates a new plane object on the heap and initializes it
 *
 * @param pos
 * @param color
 * @param orientation normalized (len == 1)
 * @return t_obj*
 */
t_obj	*new_plane(float pos[VEC3_SIZE], int color, float orientation[VEC3_SIZE])
{
	t_obj	*obj;
	t_plane	*plane;
	float	transl[VEC3_SIZE];
	float	rot[VEC3_SIZE];
	float	scale[VEC3_SIZE];

	obj = new_object(pos, color);
	obj->type = SPHERE;
	obj->specifics = malloc(sizeof(t_sphere));
	if (!obj->specifics)
		exit_fatal();
	plane = (t_plane *) obj->specifics;
	vec3_copy(orientation, plane->ovector);

	vec3(pos[0], pos[1], pos[2], transl); // just use pos!
	vec3(0, 0, 0, rot);
	vec3(1.f, 1.f, 1.f, scale);
	set_transform(transl, rot, scale, &obj->transform);

	return (obj);
}

// destroy plane()
//	free(plane);
