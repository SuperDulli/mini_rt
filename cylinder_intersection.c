/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:07:47 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 21:10:45 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
