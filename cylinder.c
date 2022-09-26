/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:09:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/26 14:23:09 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool		hit_cylinder(struct s_ray ray, t_obj *cylinder,
				float point[VEC3_SIZE], float local_normal[VEC3_SIZE]);
t_obj		*new_cylinder(
				float pos[VEC3_SIZE],
				float color[VEC3_SIZE],
				float orientation[VEC3_SIZE],
				struct s_dimension dim);
bool		close_enough(float a, float b);

static bool	intersect_to_world(t_obj *cyl, struct s_cyl_intersect *data,
				float normal[VEC3_SIZE], float point[VEC3_SIZE]);
static void	create_cylinder_matrix(t_obj *obj, float pos[VEC3_SIZE],
				float orientation[VEC3_SIZE], struct s_dimension dim);

bool	hit_cylinder(struct s_ray ray, t_obj *cylinder,
					float point[VEC3_SIZE], float local_normal[VEC3_SIZE])
{
	float					a;
	float					b;
	float					c;
	struct s_cyl_intersect	data;

	// vec3_normalize(ray.direction, ray.direction);
	data.ray = &ray;
	apply_transform(ray.direction, cylinder->transform.backward, 0,
		ray.direction);
	apply_transform(ray.origin, cylinder->transform.backward, 1, ray.origin);
	a = ray.direction[0] * ray.direction[0]
		+ ray.direction[1] * ray.direction[1];
	b = 2.f * (ray.origin[0] * ray.direction[0]
			+ ray.origin[1] * ray.direction[1]);
	c = ray.origin[0] * ray.origin[0] + ray.origin[1] * ray.origin[1] - 1.f;
	wall_intersect(a, b, c, &data);
	cap_intersect(&data);
	if ((!data.valid[0]) && (!data.valid[1])
		&& (!data.valid[2]) && (!data.valid[3]))
		return (false);
	data.min_index = find_closest_intersect(&data, point);
	return (intersect_to_world(cylinder, &data, local_normal, point));
}

bool	close_enough(float a, float b)
{
	return (fabsf(a - b) < __FLT_EPSILON__);
}

static
bool	intersect_to_world(t_obj *cyl, struct s_cyl_intersect *data,
							float normal[VEC3_SIZE], float point[VEC3_SIZE])
{
	if (data->min_index < 2)
	{
		normal_wall(cyl, point, normal);
		return (true);
	}
	else if (!close_enough(data->ray->direction[2], 0.f)
		&& sqrtf(point[0] * point[0]
			+ point[1] * point[1]) <= 1.f)
	{
		normal_cap(cyl, point, normal);
		apply_transform(point, cyl->transform.forward, 1, point);
		return (true);
	}
	return (false);
}

t_obj	*new_cylinder(
	float pos[VEC3_SIZE],
	float color[VEC3_SIZE],
	float orientation[VEC3_SIZE],
	struct s_dimension dim
)
{
	t_obj		*obj;
	t_cylinder	*cylinder;

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
	cylinder->diameter = dim.diameter;
	cylinder->height = dim.height;
	vec3_normalize(orientation, orientation);
	vec3(orientation[0], orientation[1], orientation[2], cylinder->ovector);
	create_cylinder_matrix(obj, pos, orientation, dim);
	return (obj);
}

static
void	create_cylinder_matrix(t_obj *obj, float pos[VEC3_SIZE],
						float orientation[VEC3_SIZE], struct s_dimension dim)
{
	float		v_up[VEC3_SIZE];
	float		scale[VEC3_SIZE];
	float		scale_matrix[MAT4_SIZE];

	vec3(dim.diameter / 2.f, dim.diameter / 2.f, dim.height / 2.f, scale);
	vec3(0, 1, 0, v_up);
	if (orientation[1] == 1 || orientation[1] == -1)
		vec3(1, 0, 0, v_up);
	translate_rotate(pos, orientation, v_up, &obj->transform);
	mat4_scale(scale[0], scale[1], scale[2], scale_matrix);
	mat4_mult(obj->transform.forward, scale_matrix, obj->transform.forward);
	mat4_inverse(obj->transform.forward, obj->transform.backward);
}
