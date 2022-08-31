/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:28 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/31 11:49:28 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	hit_sphere(struct s_ray *ray, t_obj *sphere);
bool	hit_cylinder(struct s_ray *ray, t_obj *cylinder, float point[VEC3_SIZE], float local_normal[VEC3_SIZE], float local_color[VEC3_SIZE]);

t_scene	*build_scene(void);

static int	close_window(t_data *data)
{
	mlx_loop_end(data->mlx);
	mlx_destroy_image(data->mlx, data->img);
	data->img = 0;
	return (0);
}

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == 65307)
		close_window(vars);
	return (0);
}

void	write_pixel(char *buffer, int pixel_addr, int color, int endian)
{
	if (endian == 1) // Most significant (Alpha) byte first
	{
		buffer[pixel_addr + 0] = (color >> 24);
		buffer[pixel_addr + 1] = (color >> 16) & 0xFF;
		buffer[pixel_addr + 2] = (color >> 8) & 0xFF;
		buffer[pixel_addr + 3] = color & 0xFF;
	}
	else if (endian == 0) // Least significant (Blue) byte first
	{
		buffer[pixel_addr + 0] = color & 0xFF;
		buffer[pixel_addr + 1] = (color >> 8) & 0xFF;
		buffer[pixel_addr + 2] = (color >> 16) & 0xFF;
		buffer[pixel_addr + 3] = (color >> 24);
	}
}


float	*ray_at(struct s_ray ray, float t, float *point)
{
	float	dir[VEC3_SIZE];

	vec3_scalar_mult(ray.direction, t, dir);
	vec3_add(ray.origin, dir, point);
	return (point);
}

unsigned int	choose_color(t_scene *scene, float u, float v)
{
	// unsigned int	color;
	t_obj		*cylinder;
	struct s_ray	ray;
	float	point[VEC3_SIZE];
	float	normal[VEC3_SIZE];
	float	pixel_color;
	float	color_v[VEC3_SIZE];
	float	ambient_color_v[VEC3_SIZE];
	t_light		*light;
	float	light_color_v[VEC3_SIZE];
	float	light_dir[VEC3_SIZE];

	cylinder = scene->objects[0];
	vec3_copy(scene->camera->pos, ray.origin); // ray.origin = camera_pos
	vec3(u, v, -1.f, ray.direction);

	// debug display u, v
	vec3(u, v, 0, color_v);
	vec3_scalar_mult(color_v, 0.5f, color_v);
	vec3(color_v[0] + 0.5f, color_v[1] + 0.5f, color_v[2] + 0.0f, color_v);
	// return (convert_to_argb(color_v));

	if (hit_cylinder(&ray, cylinder, point, normal, color_v))
	{
		// printf("u,v = %f, %f\n", u, v);
		// return convert_to_argb(normal);
		// get light direction
		vec3_sub(scene->light->pos, point, light_dir); // dir from hitpoint to light (-lightdir)
		// vec3(1, 1, 1, light_dir); // parallel light
		vec3_normalize(light_dir, light_dir);

		// colors as vectors
		color_vec_from_int(scene->ambient_light->color, ambient_color_v);
		color_vec_from_int(scene->light->colourcode, light_color_v);

		// light intensity - inverse square law? to
		vec3_scalar_mult(ambient_color_v, scene->ambient_light->ratio, ambient_color_v);
		light = (t_light *) scene->light->specifics;
		vec3_scalar_mult(light_color_v, light->brightness, light_color_v);

		// printf("colors (RGB): (%f, %f, %f) from %i\n", ambient_color_v[0], ambient_color_v[1], ambient_color_v[2], scene->light->colourcode);
		// printf("normal (xyz): (%f, %f, %f)\n", normal[0], normal[1], normal[2]);
		// printf("light_dir (xyz): (%f, %f, %f)\n", light_dir[0], light_dir[1], light_dir[2]);

		// apply shading
		pixel_color = 0;
		// pixel_color += ft_maxf(vec3_dot(color_v, ambient_color_v), 0.0f);
		pixel_color += fmaxf(vec3_dot(normal, light_dir), 0.f); // * color(obj) * color(light) // = * 1, because light is white
		// printf("pixelcolor=%f\n", pixel_color);
		vec3_scalar_mult(color_v, pixel_color, color_v);

		// map [-1, 1] -> [0, 1] -- useful for seeing the normals
		// vec3_scalar_mult(color_v, 0.5f, normal);
		// vec3(normal[0] + 0.5f, normal[1] + 0.5f, normal[2] + 0.5f, normal);
		// vec3_scalar_mult(color_v, 0.5f, color_v);
		// vec3(color_v[0] + 0.5f, color_v[1] + 0.5f, color_v[2] + 0.5f, color_v);

		return (convert_to_argb(color_v));
	}
	return (BLACK);
}

void	*fill_img(void *img)
{
	struct s_img_info	img_info;
	char				*buffer;
	struct s_2d_coord	px_coord;
	int					pixel_addr;
	int					color;
	t_scene				*scene;

	scene = build_scene();
	if (!scene)
		exit_fatal();
	buffer = mlx_get_data_addr(img, &img_info.bits_per_pixel,
			&img_info.line_size, &img_info.endian);
	px_coord.y = 0;
	while (px_coord.y < HEIGHT)
	{
		// printf("line %d of %d\n", px_coord.y, HEIGHT);
		px_coord.x = 0;
		while (px_coord.x < WIDTH)
		{
			pixel_addr = (px_coord.y * img_info.line_size) + (px_coord.x * 4);
			color = choose_color(
				scene,
				(px_coord.x / (float)WIDTH) * 2.f - 1.f,
				((px_coord.y / (float)HEIGHT) * 2.f - 1.f) * -1.f);
			write_pixel(buffer, pixel_addr, color, img_info.endian);
			px_coord.x++;
		}
		px_coord.y++;
	}
	destroy_scene(scene);
	return (img);
}

int	main(int argc, char **argv)
{
	int		window_height;
	int		window_width;
	t_data	data;
	// t_scene	*scene;

	if (argc == 2)
	{
		if (checkfile(argv[1]) == -1)
			return (0);
		// scene = new_scene(); //check failure, retunr error
		// if (store_data(argv[1], scene) == -1)
		// 	return (0);
		else
		{

			window_height = HEIGHT;
			window_width = WIDTH;
			data.mlx = mlx_init();
			data.win = mlx_new_window(data.mlx, window_width, window_height, "miniRT");
			data.img = mlx_new_image(data.mlx, window_width, window_height);
			mlx_put_image_to_window(data.mlx, data.win, fill_img(data.img), 0, 0);
			// mlx_string_put(data.mlx, data.win, 10, 10, 0x00FF0000, line);
			// free(line);
			mlx_hook(data.win, 17, (1L << 17), &close_window, &data);
			mlx_key_hook(data.win, &key_hook, &data);
			mlx_loop(data.mlx);
			mlx_destroy_window(data.mlx, data.win);
			mlx_destroy_display(data.mlx);
			free(data.mlx);
		}
	}
	else
		printf("Invalid arguments!\n");
	return (0);
}
