/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:09:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/17 16:10:31 by chelmerd         ###   ########.fr       */
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
	float	t3;
	float	t4;
	float	intersection[VEC3_SIZE];
	float	intersection2[VEC3_SIZE];
	bool	t1_valid;
	bool	t2_valid;
	bool	t3_valid;
	bool	t4_valid;
	float	t_values[4];


	radius = ((t_cylinder *) cylinder->specifics)->diameter / 2.f;

	apply_transform(ray->direction, cylinder->transform.backward, 0, ray->direction);
	apply_transform(ray->origin, cylinder->transform.backward, 1, ray->origin);
	// vec3_normalize(ray->direction, ray->direction);
	// a = vec3_length_squared(ray->direction);
	// b = 2.f * vec3_dot(ray->origin, ray->direction);
	// c = vec3_length_squared(ray->origin) - radius * radius;
	a = ray->direction[0] * ray->direction[0] + ray->direction[1] * ray->direction[1];
	b = 2.f * (ray->origin[0] * ray->direction[0] + ray->origin[1] * ray->direction[1]);
	c = ray->origin[0] * ray->origin[0] + ray->origin[1] * ray->origin[1] - radius * radius;

	discriminant = b * b - 4 * a * c;
	// printf("discriminant=%f, a=%f, b=%f, c=%f\n", discriminant, a, b, c);
	if (discriminant < 0)
		return (-1.f); // no hit

	// walls
	t = (-b - sqrtf(discriminant)) / (2.f * a);
	t2 = (-b + sqrtf(discriminant)) / (2.f * a);
	// caps
	t3 = (-1.f - ray->origin[2]) / ray->direction[2];
	t4 = (+1.f - ray->origin[2]) / ray->direction[2];

	// t = ft_minf(t, t2);
	ray_at(*ray, t, intersection);
	if (t > 0.f && fabsf(intersection[2]) < 1.0f) // clinder wall
	{
		// apply_transform(intersection, cylinder->transform.forward, 1, intersection);
		// printf("(%f,%f,%f) = wall\n", intersection[0], intersection[1], intersection[2]);
		t1_valid = true;
	}
	else
	{
		t1_valid = false;
		t = INFINITY;
	}
	ray_at(*ray, t2, intersection);
	if (t2 > 0.f && fabsf(intersection[2]) < 1.0f) // clinder wall
	{
		// apply_transform(intersection, cylinder->transform.forward, 1, intersection);
		// printf("(%f,%f,%f) = wall2\n", intersection[0], intersection[1], intersection[2]);
		t2_valid = true;
	}
	else
	{
		t2_valid = false;
		t2 = INFINITY;
	}
	ray_at(*ray, t3, intersection2);
	if (t3 > 0.f && sqrtf(intersection2[0] * intersection2[0] + intersection2[1] * intersection2[1]) < 1.f)
	{
		// apply_transform(intersection, cylinder->transform.forward, 1, intersection);
		// printf("(%f,%f,%f) = disk\n", intersection2[0], intersection2[1], intersection2[2]);
		t3_valid = true;
	}
	else
	{
		t3_valid = false;
		t3 = INFINITY;
	}
	ray_at(*ray, t4, intersection2);
	if (t4 > 0.f && sqrtf(intersection2[0] * intersection2[0] + intersection2[1] * intersection2[1]) < 1.f)
	{
		// apply_transform(intersection, cylinder->transform.forward, 1, intersection);
		// printf("(%f,%f,%f) = disk2\n", intersection2[0], intersection2[1], intersection2[2]);
		t4_valid = true;
	}
	else
	{
		t4_valid = false;
		t4 = INFINITY;
	}

	if ((!t1_valid) && (!t2_valid) && (!t3_valid) && (!t4_valid))
		return -1.f;

	t_values[0] = t;
	t_values[1] = t2;
	t_values[2] = t3;
	t_values[3] = t4;
	int	min_index;
	float	min_value;
	int i;

	min_index = 0;
	min_value = INFINITY;
	i = 0;
	while (i < 4)
	{
		if (t_values[i] < min_value)
		{
			min_value = t_values[i];
			min_index = i;
		}
		i++;
	}
	return (t_values[min_index]);
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
	vec3(M_PI_2, 0, 0, rot); // TODO calc rot from orientation
	vec3(1.f, 1.f, 1.f, scale);
	set_transform(transl, rot, scale, &obj->transform);

	return (obj);
}
