/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:03:18 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/25 11:04:00 by chelmerd         ###   ########.fr       */
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
