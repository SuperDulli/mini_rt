/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:05:34 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 20:28:48 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

unsigned int	choose_color(t_scene *scene, float u, float v);

static void		apply_shading(t_scene *scene, t_hit_record *hit,
					float color_v[VEC3_SIZE]);
static void		get_light_color(t_scene *scene, t_hit_record *hit,
					float light_dir[VEC3_SIZE], float light_color_v[VEC3_SIZE]);

unsigned int	choose_color(t_scene *scene, float u, float v)
{
	struct s_ray	ray;
	t_list			*ray_intersections;
	float			point[VEC3_SIZE];
	float			color_v[VEC3_SIZE];
	t_hit_record	*hit;

	ray_camera(scene->camera, vec3(u, v, -1, point), &ray);
	ray_intersections = NULL;
	if (!ray_intersect(&ray, scene, &ray_intersections))
	{
		ft_lstclear(&ray_intersections, free);
		exit_fatal();
	}
	if (ft_lstsize(ray_intersections) == 0)
	{
		return (BLACK);
	}
	hit = get_closest_hit(ray_intersections, scene->camera->pos);
	apply_shading(scene, hit, color_v);
	ft_lstclear(&ray_intersections, free);
	return (convert_to_argb(color_v));
}

static
void	get_light_color(t_scene *scene, t_hit_record *hit,
					float light_dir[VEC3_SIZE], float light_color_v[VEC3_SIZE])
{
	float	pixel_color;
	float	point[VEC3_SIZE];
	float	tmp[VEC3_SIZE];

	pixel_color = 0;
	pixel_color += vec3_dot(hit->normal, light_dir);
	if (pixel_color < 0)
		pixel_color = 0;
	else
	{
		vec3_scalar_mult(hit->normal, SHADOW_BIAS, tmp);
		if (intersection_with_light_ray(scene,
				vec3_add(hit->pos, tmp, point),
				distance(point, scene->light->pos)))
			pixel_color = 0;
	}
	vec3_scalar_mult(hit->color, pixel_color, light_color_v);
}

static
void	apply_shading(t_scene *scene, t_hit_record *hit,
	float color_v[VEC3_SIZE])
{
	float	ambient_color_v[VEC3_SIZE];
	t_light	*light;
	float	light_color_v[VEC3_SIZE];
	float	light_dir[VEC3_SIZE];

	vec3_copy(scene->ambient_light->color, ambient_color_v);
	vec3(hit->color[0] * ambient_color_v[0],
		hit->color[1] * ambient_color_v[1],
		hit->color[2] * ambient_color_v[2], ambient_color_v);
	vec3_scalar_mult(ambient_color_v, scene->ambient_light->ratio,
		ambient_color_v);
	vec3_sub(scene->light->pos, hit->pos, light_dir);
	vec3_normalize(light_dir, light_dir);
	get_light_color(scene, hit, light_dir, light_color_v);
	light = (t_light *) scene->light->specifics;
	vec3_scalar_mult(light_color_v, light->brightness, light_color_v);
	vec3_add(ambient_color_v, light_color_v, color_v);
}
