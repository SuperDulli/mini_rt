/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:28 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 16:04:17 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	intersection_with_light_ray(t_scene *scene, float point[VEC3_SIZE], float dis_to_light);

int	close_window(t_data *data);

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == ESC_KEY)
		close_window(vars);
	return (0);
}

/**
 * @brief writes the color value to the right pos in the img buffer.
 *
 * @param buffer 1D array that hold all the pixel values
 * @param pixel_addr pixel to change
 * @param color 0xAARRGGBB
 * @param endian which byte comes first (0/1->most/least significant byte)
 */
void	write_pixel(char *buffer, int pixel_addr, int color, int endian)
{
	if (endian == 1)
	{
		buffer[pixel_addr + 0] = (color >> 24);
		buffer[pixel_addr + 1] = (color >> 16) & 0xFF;
		buffer[pixel_addr + 2] = (color >> 8) & 0xFF;
		buffer[pixel_addr + 3] = color & 0xFF;
	}
	else if (endian == 0)
	{
		buffer[pixel_addr + 0] = color & 0xFF;
		buffer[pixel_addr + 1] = (color >> 8) & 0xFF;
		buffer[pixel_addr + 2] = (color >> 16) & 0xFF;
		buffer[pixel_addr + 3] = (color >> 24);
	}
}

float	distance(float start_point[VEC3_SIZE], float end_point[VEC3_SIZE])
{
	float	dis_vector[VEC3_SIZE];

	vec3_sub(end_point, start_point, dis_vector);
	return (vec3_length(dis_vector));
}

void	apply_shading(t_scene *scene, float	point[VEC3_SIZE], float	normal[VEC3_SIZE], float color_v[VEC3_SIZE])
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

void	*fill_img(void *img, t_scene *scene)
{
	struct s_img_info	img_info;
	char				*buffer;
	struct s_2d_coord	px_coord;
	int					pixel_addr;
	int					color;
	float				aspectratio;

	aspectratio = (float)WIDTH / (float)HEIGHT;

	buffer = mlx_get_data_addr(img, &img_info.bits_per_pixel,
			&img_info.line_size, &img_info.endian);
	px_coord.y = 0;
	while (px_coord.y < HEIGHT)
	{
		printf("line %d of %d\n", px_coord.y, HEIGHT);
		px_coord.x = 0;
		while (px_coord.x < WIDTH) // Raster space
		{
			pixel_addr = (px_coord.y * img_info.line_size) + (px_coord.x * 4); // raster space (2D) -> 1D
			color = choose_color(
				scene,
				((px_coord.x / (float)WIDTH) * 2.f - 1.f) * aspectratio * tan(scene->camera->fov / 2 * M_PI / 180),
				(((px_coord.y / (float)HEIGHT) * 2.f - 1.f) * -1.f) * tan(scene->camera->fov / 2 * M_PI / 180));
			write_pixel(buffer, pixel_addr, color, img_info.endian);
			px_coord.x++;
		}
		px_coord.y++;
	}
	return (img);
}

int	main(int argc, char **argv)
{
	int		window_height;
	int		window_width;
	t_data	data;
	t_scene	*scene;

	if (argc == 2)
	{
		if (checkfile(argv[1]) == -1)
			return (1);
		scene = new_scene();
		if (store_data(argv[1], scene) == -1)
		{
			destroy_scene(scene);
			return (1);
		}
		else
		{
			window_height = HEIGHT;
			window_width = WIDTH;
			data.mlx = mlx_init();
			data.win = mlx_new_window(data.mlx, window_width, window_height, "miniRT");
			data.img = mlx_new_image(data.mlx, window_width, window_height);
			mlx_put_image_to_window(data.mlx, data.win, fill_img(data.img, scene), 0, 0);
			destroy_scene(scene);
			mlx_hook(data.win, 17, (1L << 17), &close_window, &data);
			mlx_key_hook(data.win, &key_hook, &data);
			mlx_loop(data.mlx);
		}
	}
	else
		ft_putendl_fd("Invalid arguments!", 1);
	return (0);
}
