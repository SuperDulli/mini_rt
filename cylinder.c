/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:09:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/16 14:19:56 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	*ray_at(struct s_ray ray, float t, float *point);

float	hit_cylinder(struct s_ray *ray, t_obj *cylinder)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	radius;

	float	t;
	float	t2;
	float	intersection[VEC3_SIZE];

	radius = ((t_cylinder *) cylinder->specifics)->diameter / 2.f;

	apply_transform(ray->direction, cylinder->transform.backward, 0, ray->direction);
	apply_transform(ray->origin, cylinder->transform.backward, 1, ray->origin);
	a = vec3_length_squared(ray->direction);
	b = 2.f * vec3_dot(ray->origin, ray->direction);
	c = vec3_length_squared(ray->origin) - radius * radius;

	discriminant = b * b - 4 * a * c;
	// printf("discriminant=%f, a=%f, b=%f, c=%f\n", discriminant, a, b, c);
	if (discriminant < 0)
		return (-1.f); // no hit
	return ((-b - sqrtf(discriminant)) / (2.f * a));
}

t_obj	*new_cylinder(
	float pos[VEC3_SIZE],
	int color,
	float orientation[VEC3_SIZE],
	float diameter,
	float height
)
{
	t_obj		*obj;
	t_cylinder	*cylinder;
	float		transl[VEC3_SIZE];
	float		rot[VEC3_SIZE];
	float		scale[VEC3_SIZE];

	obj = new_object(pos, color);
	obj->type = CYLINDER;
	obj->specifics = malloc(sizeof(t_cylinder));
	if (!obj->specifics)
		exit_fatal();
	cylinder = (t_cylinder *) obj->specifics;
	cylinder->diameter = diameter;
	cylinder->height = height;
	vec3(orientation[0], orientation[1], orientation[2], cylinder->ovector);

	vec3(pos[0], pos[1], pos[2], transl); // just use pos!
	vec3(90, 0, 0, rot); // TODO calc rot from orientation
	vec3(1.f, 1.f, 1.f, scale);
	set_transform(transl, rot, scale, &obj->transform);

	return (obj);
}
