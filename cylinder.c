/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:09:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 19:19:39 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

struct s_cyl_intersect
{
	float			t_values[4];
	float			intersection[VEC3_SIZE];
	bool			valid[4];
	int				min_index;
	struct s_ray	*ray;
};

// in this file:

static void	normal_wall(t_obj *cylinder, float point[VEC3_SIZE], float normal[VEC3_SIZE]);
static void	normal_cap(t_obj *cylinder, float point[VEC3_SIZE], float normal[VEC3_SIZE]);
static void	wall_intersect(float a, float b, float c, struct s_cyl_intersect *data);
static void	cap_intersect(struct s_cyl_intersect *data);
static int	find_closest_intersect(struct s_cyl_intersect *data, float point[VEC3_SIZE]);
static bool	intersect_to_world(t_obj *cyl, struct s_cyl_intersect *data, float normal[VEC3_SIZE], float point[VEC3_SIZE]);

bool	close_enough(float a, float b)
{
	return (fabsf(a - b) < __FLT_EPSILON__);
}

bool	hit_cylinder(struct s_ray ray, t_obj *cylinder,
					float point[VEC3_SIZE], float local_normal[VEC3_SIZE])
{
	float					a;
	float					b;
	float					c;
	struct s_cyl_intersect	data;

	vec3_normalize(ray.direction, ray.direction);
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

static
int	find_closest_intersect(struct s_cyl_intersect *data, float point[VEC3_SIZE])
{
	int		min_index;
	float	min_value;
	int		i;

	min_index = 0;
	min_value = INFINITY;
	i = 0;
	while (i < 4)
	{
		if (data->valid[i] && data->t_values[i] < min_value)
		{
			min_value = data->t_values[i];
			min_index = i;
		}
		i++;
	}
	ray_at(data->ray, min_value, point);
	return (min_index);
}

static
void	wall_intersect(float a, float b, float c, struct s_cyl_intersect *data)
{
	float	discriminant;

	discriminant = b * b - 4 * a * c;
	data->valid[0] = false;
	data->valid[1] = false;
	data->t_values[0] = INFINITY;
	data->t_values[1] = INFINITY;
	if (discriminant >= 0)
	{
		data->t_values[0] = (-b - sqrtf(discriminant)) / (2.f * a);
		data->t_values[1] = (-b + sqrtf(discriminant)) / (2.f * a);
		ray_at(data->ray, data->t_values[0], data->intersection);
		if (data->t_values[0] > 0.f && fabsf(data->intersection[2]) < 1.f)
			data->valid[0] = true;
		ray_at(data->ray, data->t_values[1], data->intersection);
		if (data->t_values[1] > 0.f && fabsf(data->intersection[2]) < 1.f)
			data->valid[1] = true;
	}
}

static
void	cap_intersect(struct s_cyl_intersect *data)
{
	data->valid[2] = false;
	data->valid[3] = false;
	data->t_values[2] = INFINITY;
	data->t_values[3] = INFINITY;
	if (close_enough(data->ray->direction[2], 0.f))
		return ;
	data->t_values[2] = (-1.f - data->ray->origin[2]) / data->ray->direction[2];
	data->t_values[3] = (+1.f - data->ray->origin[2]) / data->ray->direction[2];
	ray_at(data->ray, data->t_values[2], data->intersection);
	if (data->t_values[2] > 0.f
		&& sqrtf(data->intersection[0] * data->intersection[0]
			+ data->intersection[1] * data->intersection[1]) <= 1.f)
		data->valid[2] = true;
	ray_at(data->ray, data->t_values[3], data->intersection);
	if (data->t_values[3] > 0.f
		&& sqrtf(data->intersection[0] * data->intersection[0]
			+ data->intersection[1] * data->intersection[1]) <= 1.f)
		data->valid[3] = true;
}

static
void	normal_wall(t_obj *cyl, float point[VEC3_SIZE], float normal[VEC3_SIZE])
{
	float	tmp_normal[VEC3_SIZE];
	float	origin[VEC3_SIZE];

	vec3(point[0], point[1], 0.f, tmp_normal);
	apply_transform(point, cyl->transform.forward, 1, point);
	vec_fill(0.f, 3, origin);
	apply_transform(origin, cyl->transform.forward, 1, origin);
	apply_transform(tmp_normal, cyl->transform.forward, 1, tmp_normal);
	vec3_sub(tmp_normal, origin, tmp_normal);
	vec3_normalize(tmp_normal, tmp_normal);
	vec3_copy(tmp_normal, normal);
}

static
void	normal_cap(t_obj *cyl, float point[VEC3_SIZE], float normal[VEC3_SIZE])
{
	float	tmp_normal[VEC3_SIZE];
	float	origin[VEC3_SIZE];

	vec3(0.f, 0.f, point[2], tmp_normal);
	vec_fill(0.f, 3, origin);
	apply_transform(origin, cyl->transform.forward, 1, origin);
	apply_transform(tmp_normal, cyl->transform.forward, 1, tmp_normal);
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
	float		v_up[VEC3_SIZE];
	float		scale[VEC3_SIZE];
	float		scale_matrix[MAT4_SIZE];

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
	vec3_normalize(orientation, orientation);
	vec3(orientation[0], orientation[1], orientation[2], cylinder->ovector);
	vec3(diameter / 2.f, diameter / 2.f, height / 2.f, scale);

	vec3(0, 1, 0, v_up);
	if (orientation[1] == 1 || orientation[1] == -1)
		vec3(1, 1, 0, v_up);
	translate_rotate(pos, orientation, v_up, &obj->transform);
	mat4_scale(scale[0], scale[1], scale[2], scale_matrix);
	mat4_mult(obj->transform.forward, scale_matrix, obj->transform.forward);
	mat4_inverse(obj->transform.forward, obj->transform.backward);
	return (obj);
}
