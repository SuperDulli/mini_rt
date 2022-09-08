/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:03:18 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/08 15:06:36 by chelmerd         ###   ########.fr       */
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

void	ray_cast(t_camera *camera, float *point, struct s_ray *ray)
{
	float	origin[VEC3_SIZE];

	apply_transform(camera->pos, camera->transform.backward, 1, origin);
	apply_transform(point, camera->transform.backward, 1, point);
	vec3_copy(origin, ray->origin);
	vec3_sub(point, origin, ray->direction);
}

bool	ray_intersect(struct s_ray *ray, t_scene *scene, t_list **intersections)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (i < scene->obj_count)
	{
		obj = get_obj_from_scene(scene, i);
		if (!hit_object(obj, ray, intersections))
			return (false);
		i++;
	}
	return (true);
}

bool	hit_object(t_obj *obj, struct s_ray *ray, t_list **intersections)
{
	float	point[VEC3_SIZE];
	float	normal[VEC3_SIZE];

	if (obj->type == SPHERE)
	{
		if (hit_sphere(*ray, obj, point, normal))
		{
			if (!add_hit_record(intersections, new_hit_record(point, normal, obj->color)))
			{
				ft_error(1, "ray_intersect: cannot add sphere hit to list of intersections.");
				return (false);
			}
		}
	}
	else if (obj->type == PLANE)
	{
		if (hit_plane(*ray, obj, point, normal))
		{
			if (!add_hit_record(intersections, new_hit_record(point, normal, obj->color)))
			{
				ft_error(1, "ray_intersect: cannot add plane hit to list of intersections.");
				return (false);
			}
		}
	}
	else if (obj->type == CYLINDER)
	{
		if (hit_cylinder(*ray, obj, point, normal))
		{
			if (!add_hit_record(intersections, new_hit_record(point, normal, obj->color)))
			{
				ft_error(1, "ray_intersect: cannot add cylinder hit to list of intersections.");
				return (false);
			}
		}
	}
	return (true);
}
