/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:02:38 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/04 16:59:01 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

unsigned int	get_color(unsigned alpha, unsigned r, unsigned g, unsigned b)
{
	unsigned int	color;

	color = 0;
	color += (alpha << 24);
	color += (r << 16);
	color += (g << 8);
	color += b;
	return (color);
}

float	*color_vec(float color[VEC3_SIZE], float *result)
{
	const float	divisor = 255.f;

	if (0 > color[0] || color[0] > 255 || 0 > color[1] || color[1] > 255 || \
		0 > color[2] || color[2] > 255)
	{
		ft_error(1, "colors not in 0 to 255 range.");
	}
	result = vec3(color[0] / divisor, color[1] / divisor, color[2] / divisor, \
				result);
	return (result);
}

int	convert_to_argb(float rgb[VEC3_SIZE])
{
	int	color;
	int	red;
	int	green;
	int	blue;

	vec3_clamp(rgb, 0.0f, 1.0f, rgb);
	if (0.f > rgb[0] || rgb[0] > 1.f || 0.f > rgb[1] || rgb[1] > 1.f || \
		0.f > rgb[2] || rgb[2] > 1.f)
	{
		printf("rgb(%f,%f,%f)\n", rgb[0], rgb[1], rgb[2]);
		ft_error(1, "colors not in 0.0 to 1.0 range.");
	}
	red = rgb[0] * 255;
	green = rgb[1] * 255;
	blue = rgb[2] * 255;
	color = (0 << 24) | (red << 16) | (green << 8) | blue;
	return (color);
}

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
	vec3_copy(hit->color, color_v);
	apply_shading(scene, hit->pos, hit->normal, color_v);
	ft_lstclear(&ray_intersections, free);
	return (convert_to_argb(color_v));
}

void	apply_shading(t_scene *scene, float point[VEC3_SIZE], float normal[VEC3_SIZE], float color_v[VEC3_SIZE])
{
	float	ambient_color_v[VEC3_SIZE];
	t_light	*light;
	float	light_color_v[VEC3_SIZE];
	float	light_dir[VEC3_SIZE];
	float	pixel_color;

	vec3_sub(scene->light->pos, point, light_dir);
	vec3_normalize(light_dir, light_dir);
	vec3_copy(scene->ambient_light->color, ambient_color_v);
	vec3_copy(scene->light->color, light_color_v);
	vec3_scalar_mult(ambient_color_v, scene->ambient_light->ratio, ambient_color_v);
	light = (t_light *) scene->light->specifics;
	vec3(color_v[0] * ambient_color_v[0], color_v[1] * ambient_color_v[1], color_v[2] * ambient_color_v[2], ambient_color_v);
	pixel_color = 0;
	pixel_color += vec3_dot(normal, light_dir);
	if (pixel_color < 0)
		pixel_color = 0;
	else
	{
		if (intersection_with_light_ray(
			scene,
			vec3_add(point, vec3_scalar_mult(normal, SHADOW_BIAS, normal), point),
			distance(point, scene->light->pos)))
			pixel_color = 0;
	}
	vec3_scalar_mult(color_v, pixel_color, light_color_v);
	vec3_scalar_mult(light_color_v, light->brightness, light_color_v);
	vec3_add(ambient_color_v, light_color_v, color_v);
}
