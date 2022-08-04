/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:38:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/04 14:53:37 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief tests where the ray hits the sphere
 *
 * ABC formula to solve quadratic equation like t^2 * a + t * b + c = 0
 * t = (-b - sqrt(b^2 - 4ac)) / 2a
 *
 * @param ray
 * @param sphere
 * @return float the closest hit point
 */
float	hit_sphere(struct s_ray ray, t_obj *sphere)
{
	float	oc[VEC3_SIZE];
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_sphere	*sphere_info;
	float	radius;

	sphere_info = (t_sphere *) sphere->specifics;
	radius = sphere_info->diameter / 2.f;
	vec3_sub((float *) &ray.origin, (float *) &sphere->pos, oc);
	a = vec3_length_squared((float *) &ray.direction);
	b = 2.0f * vec3_dot(oc, (float *) &ray.direction);
	c = vec3_length_squared(oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.f);
	return ((-b - sqrtf(discriminant)) / (2.f * a));
}

void	exit_fatal(void)
{
	printf("Fatal error.\n");
	exit(1);
}

t_obj	*new_object(float pos[VEC3_SIZE], int color)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		exit_fatal();
	obj->typ = NONE;
	obj->specifics = NULL;
	obj->colourcode = color;
	obj->pos[0] = pos[0];
	obj->pos[1] = pos[1];
	obj->pos[2] = pos[2];

	return (obj);
}

t_obj	*new_sphere(float pos[VEC3_SIZE], int color, float diameter)
{
	t_obj		*obj;
	t_sphere	*sphere;

	obj = new_object(pos, color);
	obj->typ = SPHERE;
	obj->specifics = malloc(sizeof(t_sphere));
	if (!obj->specifics)
		exit_fatal();
	sphere = (t_sphere *) obj->specifics;
	sphere->diameter = diameter;

	return (obj);
}

static
void	destroy_sphere(t_sphere *sphere)
{
	if (!sphere)
		return ;
	free(sphere);
}

void	destroy_object(t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->typ == SPHERE)
		destroy_sphere((t_sphere *) obj->specifics);
	free(obj);
}

