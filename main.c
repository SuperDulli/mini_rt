/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:28 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/04 16:16:41 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	hit_sphere(struct s_ray *ray, t_obj *sphere);
bool	hit_cylinder(struct s_ray *ray, t_obj *cylinder, float point[VEC3_SIZE], float local_normal[VEC3_SIZE]); //, float local_color[VEC3_SIZE]);

t_scene	*build_scene(void);

static int	close_window(t_data *data)
{
	#ifdef __linux__
	mlx_loop_end(data->mlx);
	#endif
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	#ifdef __linux__
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	#endif
	exit(0);
	// data->img = 0;
	return (0);
}

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == ESC_KEY)
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

void	apply_shading(t_scene *scene, float	point[VEC3_SIZE], float	normal[VEC3_SIZE], float color_v[VEC3_SIZE])
{
	float	ambient_color_v[VEC3_SIZE];
	t_light	*light;
	float	light_color_v[VEC3_SIZE];
	float	light_dir[VEC3_SIZE];
	float	pixel_color;

	// get light direction
	vec3_sub(scene->light->pos, point, light_dir); // dir from hitpoint to light (-lightdir)
	// vec3(1, 1, 1, light_dir); // parallel light
	vec3_normalize(light_dir, light_dir);

	// colors as vectors
	vec3_copy(scene->ambient_light->color, ambient_color_v);
	vec3_copy(scene->light->color, light_color_v); // TODO: cast ray towards light to check if its blocked

	// light intensity - inverse square law? to
	vec3_scalar_mult(ambient_color_v, scene->ambient_light->ratio, ambient_color_v);
	light = (t_light *) scene->light->specifics;
	vec3_scalar_mult(light_color_v, light->brightness, light_color_v);

	// apply shading
	vec3(color_v[0] * ambient_color_v[0], color_v[1] * ambient_color_v[1], color_v[2] * ambient_color_v[2], ambient_color_v);

	pixel_color = 0;
	pixel_color += fmaxf(vec3_dot(normal, light_dir), 0.f); // * color(obj) * color(light) // = * 1, because light is white
	vec3_scalar_mult(color_v, pixel_color, light_color_v);
	vec3_add(ambient_color_v, light_color_v, color_v);
}

unsigned int	choose_color(t_scene *scene, float u, float v)
{
	t_obj		*cylinder;
	struct s_ray	ray;
	float	point[VEC3_SIZE];
	float	normal[VEC3_SIZE];
	float	color_v[VEC3_SIZE];

	cylinder = get_obj_from_scene(scene, 2);
	vec3_copy(scene->camera->pos, ray.origin); // ray.origin = camera_pos
	vec3(u, v, -1.f, ray.direction);

	if (hit_cylinder(&ray, cylinder, point, normal))
	{
		vec3_copy(cylinder->color, color_v);
		apply_shading(scene, point, normal, color_v);
		return (convert_to_argb(color_v));
	}
	return (BLACK);
}

void	*fill_img(void *img, t_scene *scene)
{
	struct s_img_info	img_info;
	char				*buffer;
	struct s_2d_coord	px_coord;
	int					pixel_addr;
	int					color;

	buffer = mlx_get_data_addr(img, &img_info.bits_per_pixel,
			&img_info.line_size, &img_info.endian);
	px_coord.y = 0;
	while (px_coord.y < HEIGHT)
	{
		printf("line %d of %d\n", px_coord.y, HEIGHT);
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
			return (0);
		scene = new_scene();
		if (store_data(argv[1], scene) == -1)
		{
			destroy_scene(scene);
			return (0);
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
