/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:28 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/11 16:16:52 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	hit_sphere(struct s_ray *ray, t_obj *sphere);
float	hit_plane(struct s_ray *ray, t_obj *plane);

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
	t_obj		*plane;
	t_obj		*plane2;
	struct s_ray	ray;
	float	t;
	float	t2;

	plane = scene->objects[0];
	plane2 = scene->objects[1];
	vec3_copy(scene->camera->pos, ray.origin); // ray.origin = camera_pos
	vec3(u, v, -1.f, ray.direction);
	t = hit_plane(&ray, plane);
	t2 = hit_plane(&ray, plane2);
	if ((t == 0.f && t2 == 0.f) || t == t2 || t < 0.f || t2 < 0.0f)
		return BLACK;
	if (t < t2)
		return plane->colourcode;
	return plane2->colourcode;
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
	(void) scene;
	buffer = mlx_get_data_addr(img, &img_info.bits_per_pixel,
			&img_info.line_size, &img_info.endian);
	px_coord.y = 0;
	while (px_coord.y < HEIGHT)
	{
		px_coord.x = 0;
		while (px_coord.x < WIDTH)
		{
			pixel_addr = (px_coord.y * img_info.line_size) + (px_coord.x * 4);
			color = choose_color(
				scene,
				(px_coord.x / (float)WIDTH) * 2.f - 1.f, // -1 -> 1
				((px_coord.y / (float)HEIGHT) * 2.f - 1.f) * -1.f); // 1 -> -1, flip upside down
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
	// char	*line;

	// line = get_next_line(1);

	if (argc == 2)
	{
		if (checkfile(argv[1]) == -1)
			return (0);
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
