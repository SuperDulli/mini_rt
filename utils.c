/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:18:49 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 21:06:27 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	exit_fatal(void)
{
	printf("Fatal error.\n");
	exit(1);
}

void	*new(size_t size)
{
	void	*n;

	n = malloc(size);
	if (!n)
	{
		ft_error(1, "malloc failed.");
		return (NULL);
	}
	return (n);
}

bool	intersection_with_light_ray(t_scene *scene,
			float point[VEC3_SIZE], float dis_to_light)
{
	struct s_ray	light_ray;
	float			dis_to_intersect;
	t_obj			*obj;
	int				i;
	t_hit_record	hit;

	ray_cast(point, scene->light->pos, &light_ray);
	i = 0;
	while (i < scene->obj_count)
	{
		obj = get_obj_from_scene(scene, i);
		if (hit_object(obj, &light_ray, &hit))
		{
			dis_to_intersect = distance(light_ray.origin, hit.pos);
			if (dis_to_intersect < dis_to_light)
				return (true);
		}
		i++;
	}
	return (false);
}

float	distance(float start_point[VEC3_SIZE], float end_point[VEC3_SIZE])
{
	float	dis_vector[VEC3_SIZE];

	vec3_sub(end_point, start_point, dis_vector);
	return (vec3_length(dis_vector));
}

float	ufo(int pixel, struct s_img_info img_info, t_scene *scene, \
		int coordinate)
{
	if (coordinate)
		return (((pixel / (float)WIDTH) * 2.f - 1.f) * img_info.aspectratio * \
				tan(scene->camera->fov / 2 * M_PI / 180));
	else
		return ((((pixel / (float)HEIGHT) * 2.f - 1.f) * -1.f) * \
				tan(scene->camera->fov / 2 * M_PI / 180));
}
