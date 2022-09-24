/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:03:18 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/23 14:43:35 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	*ray_at(struct s_ray *ray, float t, float *point)
{
	float	dir[VEC3_SIZE];

	vec3_scalar_mult(ray->direction, t, dir);
	vec3_add(ray->origin, dir, point);
	return (point);
}

void	ray_cast(float *origin, float *point, struct s_ray *ray)
{
	vec3_copy(origin, ray->origin);
	vec3_sub(point, origin, ray->direction);
}

void	ray_camera(t_camera *camera, float *point, struct s_ray *ray)
{
	vec_fill(0.f, 3, ray->origin);
	apply_transform(ray->origin, camera->transform.forward, 1, ray->origin);
	apply_transform(point, camera->transform.forward, 1, point);
	vec3_sub(point, ray->origin, ray->direction);
}

bool	ray_intersect(struct s_ray *ray, t_scene *scene, t_list **intersections)
{
	int				i;
	t_obj			*obj;
	t_hit_record	hit;

	i = 0;
	while (i < scene->obj_count)
	{
		obj = get_obj_from_scene(scene, i);
		if (hit_object(obj, ray, &hit))
		{
			if (!add_hit_record(intersections, new_hit_record(hit.pos, \
				hit.normal, hit.color)))
			{
				ft_error(1, "ray_intersect: cannot add intersection to list.");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	hit_object(t_obj *obj, struct s_ray *ray, t_hit_record *hit)
{
	float	point[VEC3_SIZE];
	float	normal[VEC3_SIZE];

	if (obj->type == SPHERE)
	{
		if (hit_sphere(*ray, obj, point, normal))
		{
			vec3_copy(point, hit->pos);
			vec3_copy(normal, hit->normal);
			vec3_copy(obj->color, hit->color);
			return (true);
		}
	}
	else if (obj->type == PLANE)
	{
		if (hit_plane(*ray, obj, point, normal))
		{
			vec3_copy(point, hit->pos);
			vec3_copy(normal, hit->normal);
			vec3_copy(obj->color, hit->color);
			return (true);
		}
	}
	else if (obj->type == CYLINDER)
	{
		if (hit_cylinder(*ray, obj, point, normal))
		{
			vec3_copy(point, hit->pos);
			vec3_copy(normal, hit->normal);
			vec3_copy(obj->color, hit->color);
			return (true);
		}
	}
	return (false);
}
