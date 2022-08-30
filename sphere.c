/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:38:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/30 12:40:25 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief tests where the ray hits the sphere
 *
 * ABC formula to solve quadratic equation like t^2 * a + t * b + c = 0
 * t = (-b - sqrt(b^2 - 4ac)) / 2a
 *
 * @param ray
 * @param sphere
 * @return float the closest hit point, or -1 if it missed the sphere
 */
float	hit_sphere(struct s_ray *ray, t_obj *sphere)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	radius;

	radius = ((t_sphere *) sphere->specifics)->diameter / 2.f;

	apply_transform(ray->direction, sphere->transform.backward, 0, ray->direction);
	apply_transform(ray->origin, sphere->transform.backward, 1, ray->origin);
	a = vec3_length_squared(ray->direction);
	b = 2.f * vec3_dot(ray->origin, ray->direction);
	c = vec3_length_squared(ray->origin) - radius * radius;

	discriminant = b * b - 4 * a * c;
	// printf("discriminant=%f, a=%f, b=%f, c=%f\n", discriminant, a, b, c);
	if (discriminant < 0)
		return (-1.f);
	return ((-b - sqrtf(discriminant)) / (2.f * a));
}

t_obj	*new_sphere(float pos[VEC3_SIZE], int color, float diameter)
{
	t_obj		*obj;
	t_sphere	*sphere;
	float		transl[VEC3_SIZE];
	float		rot[VEC3_SIZE];
	float		scale[VEC3_SIZE];

	obj = new_object(pos, color);
	if (!obj)
		return (NULL);
	obj->specifics = new(sizeof(t_sphere));
	if (!obj->specifics)
	{
		destroy_object(obj);
		return (NULL);
	}
	obj->type = SPHERE;
	sphere = (t_sphere *) obj->specifics;
	sphere->diameter = diameter;

	vec3(pos[0], pos[1], pos[2], transl); // just use pos!
	vec3(0, 0, 0, rot);
	vec3(1.f, 1.f, 1.f, scale);
	set_transform(transl, rot, scale, &obj->transform);

	return (obj);
}