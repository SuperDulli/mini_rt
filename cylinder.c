/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:09:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/06 12:14:44 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// in this file:

static void	normal_curved(t_obj *cylinder, float point[VEC3_SIZE], float normal[VEC3_SIZE]);
static void	normal_cap(t_obj *cylinder, float point[VEC3_SIZE], float normal[VEC3_SIZE]);


bool	close_enough(float a, float b)
{
	return (fabsf(a - b) < __FLT_EPSILON__);
}

bool	hit_cylinder(struct s_ray *ray, t_obj *cylinder, float point[VEC3_SIZE], float local_normal[VEC3_SIZE]) //, float local_color[VEC3_SIZE])
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


	radius = 1.f;

	apply_transform(ray->direction, cylinder->transform.backward, 0, ray->direction);
	apply_transform(ray->origin, cylinder->transform.backward, 1, ray->origin);
	// vec3_normalize(ray->direction, ray->direction);
	a = ray->direction[0] * ray->direction[0] + ray->direction[1] * ray->direction[1];
	b = 2.f * (ray->origin[0] * ray->direction[0] + ray->origin[1] * ray->direction[1]);
	c = ray->origin[0] * ray->origin[0] + ray->origin[1] * ray->origin[1] - radius * radius;

	discriminant = b * b - 4 * a * c;
	// printf("discriminant=%f, a=%f, b=%f, c=%f\n", discriminant, a, b, c);
	if (discriminant >= 0)
	{
		// walls
		t = (-b - sqrtf(discriminant)) / (2.f * a);
		t2 = (-b + sqrtf(discriminant)) / (2.f * a);

		ray_at(ray, t, intersection);
		if (t > 0.f && fabsf(intersection[2]) < 1.0f) // clinder wall
		{
			t1_valid = true;
		}
		else
		{
			t1_valid = false;
			t = INFINITY;
		}
		ray_at(ray, t2, intersection);
		if (t2 > 0.f && fabsf(intersection[2]) < 1.0f) // clinder wall
		{
			t2_valid = true;
		}
		else
		{
			t2_valid = false;
			t2 = INFINITY;
		}
	}
	else
	{
		t1_valid = false;
		t2_valid = false;
		t = INFINITY;
		t2 = INFINITY;
	}

	// caps
	if (close_enough(ray->direction[2], 0.f))
	{
		t3_valid = false;
		t4_valid = false;
		t3 = INFINITY;
		t4 = INFINITY;
	}
	else
	{
		//t3 = (z_min - z_origin) / z_dir
		t3 = (-1.f - ray->origin[2]) / ray->direction[2];
		t4 = (+1.f - ray->origin[2]) / ray->direction[2];
		// printf("t: %f, %f\n", t3, t4);


		ray_at(ray, t3, intersection2);
		if (t3 > 0.f && sqrtf(intersection2[0] * intersection2[0] + intersection2[1] * intersection2[1]) <= radius)
		{
			t3_valid = true;
		}
		else
		{
			t3_valid = false;
			t3 = INFINITY;
		}
		ray_at(ray, t4, intersection2);
		if (t4 > 0.f && sqrtf(intersection2[0] * intersection2[0] + intersection2[1] * intersection2[1]) <= radius)
		{
			t4_valid = true;
		}
		else
		{
			t4_valid = false;
			t4 = INFINITY;
		}
	}


	if ((!t1_valid) && (!t2_valid) && (!t3_valid) && (!t4_valid))
		return (false);

	// find closest hit point
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

	ray_at(ray, min_value, intersection);
	vec3_copy(intersection, point);
	// local_color = color_vec_from_int(cylinder->colourcode, local_color);
	// wall or caps?
	if (min_index < 2)
	{
		normal_curved(cylinder, intersection, local_normal);
		// local_color[2] = 1.f;
		return (true);
	}
	else if (!close_enough(ray->direction[2], 0.f) && sqrtf(intersection[0] * intersection[0] + intersection[1] * intersection[1]) <= radius)
	{
		// printf("cap normal (xyz): (%f, %f, %f) min_index=%d\n", intersection[0], intersection[1], intersection[2], min_index);
		normal_cap(cylinder, intersection, local_normal);
		// printf("cap\n"); // this should be hit but its not??!?!
		return (true);
	}

	return (false);
}

static
void	normal_curved(t_obj *cylinder, float point[VEC3_SIZE], float normal[VEC3_SIZE])
{
	float	tmp_normal[VEC3_SIZE];
	float	origin[VEC3_SIZE];

	vec3(point[0], point[1], 0.f, tmp_normal);
	apply_transform(point, cylinder->transform.forward, 1, point);
	vec_fill(0.f, 3, origin);
	apply_transform(origin, cylinder->transform.forward, 1, origin);
	apply_transform(tmp_normal, cylinder->transform.forward, 1, tmp_normal);
	vec3_sub(tmp_normal, origin, tmp_normal);
	vec3_normalize(tmp_normal, tmp_normal);
	vec3_copy(tmp_normal, normal);
}

static
void	normal_cap(t_obj *cylinder, float point[VEC3_SIZE], float normal[VEC3_SIZE])
{
	float	tmp_normal[VEC3_SIZE];
	float	origin[VEC3_SIZE];

	// apply_transform(point, cylinder->transform.forward, 1, tmp_normal);
	vec3(0.f, 0.f, point[2], tmp_normal);
	vec_fill(0.f, 3, origin);
	apply_transform(origin, cylinder->transform.forward, 1, origin);
	apply_transform(tmp_normal, cylinder->transform.forward, 1, tmp_normal);
	vec3_sub(tmp_normal, origin, tmp_normal);
	vec3_normalize(tmp_normal, tmp_normal);
	vec3_copy(tmp_normal, normal);
}


t_obj	*new_cylinder(
	float pos[VEC3_SIZE],
	float color[VEC3_SIZE],
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
	if (!obj)
		return (NULL);
	obj->specifics = new(sizeof(t_cylinder));
	if (!obj->specifics)
	{
		destroy_object(obj);
		return (NULL);
	}
	obj->type = CYLINDER;
	cylinder = (t_cylinder *) obj->specifics;
	cylinder->diameter = diameter;
	cylinder->height = height;
	vec3(orientation[0], orientation[1], orientation[2], cylinder->ovector);

	vec3(pos[0], pos[1], pos[2], transl); // just use pos!
	rot_vec_from_orientation(orientation, rot);
	vec3(diameter / 2.f, diameter / 2.f, height / 2.f, scale);
	set_transform(transl, rot, scale, &obj->transform);

	return (obj);
}
