/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:03:18 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/06 16:18:11 by chelmerd         ###   ########.fr       */
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

bool	ray_intersect(struct s_ray *ray, t_scene *scene, t_list **intersections)
{
	int		i;
	t_obj	*obj;
	float	point[VEC3_SIZE];
	float	normal[VEC3_SIZE];

	i = 0;
	while (i < scene->obj_count)
	{
		obj = get_obj_from_scene(scene, i);
		if (obj->type == CYLINDER)
		{
			if (hit_cylinder(ray, obj, point, normal))
			{
				if (!add_hit_record(intersections, new_hit_record(point, normal, obj->color)))
				{
					ft_error(1, "ray_intersect: cannot add cylinder hit to list of intersections.");
					return (false);
				}
			}
		}
		else if (obj->type == SPHERE)
		{
			if (hit_sphere(ray, obj, point, normal))
			{
				if (!add_hit_record(intersections, new_hit_record(point, normal, obj->color)))
				{
					ft_error(1, "ray_intersect: cannot add sphere hit to list of intersections.");
					return (false);
				}
			}
		}
		i++;
	}
	return (true);
}
