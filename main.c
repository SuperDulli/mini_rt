/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:28 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/02 18:47:14 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

float	hit_sphere(struct s_ray ray, struct s_sphere sphere)
{
	float	oc[VEC3_SIZE];
	float	a;
	float	b;
	float	c;
	float	discriminant;

	vec3_sub((float *)&ray.origin, (float *)&sphere.center, oc);
	a = vec3_length_squared((float *)&ray.direction);
	b = 2.0f * vec3_dot(oc, (float *)&ray.direction);
	c = vec3_length_squared(oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.f);
	return ((-b - sqrtf(discriminant)) / (2.f * a));
}

float	*ray_at(struct s_ray ray, float t, float *point)
{
	float	dir[VEC3_SIZE];

	vec3_scalar_mult(ray.direction, t, dir);
	vec3_add(ray.origin, dir, point);
	return (point);
}

unsigned int	choose_color(float u, float v)
{
	unsigned int	color;
	struct s_sphere	sphere;
	float	camera_pos[VEC3_SIZE];
	float	camera_dir[VEC3_SIZE];
	float	pixel_pos[VEC3_SIZE];
	struct s_ray	ray;
	float	t;
	float	normal[VEC3_SIZE];
	float	tmp[VEC3_SIZE];

	vec3(0, 0, 0, sphere.center);
	sphere.radius = 1.f;
	sphere.color = 0x000000FF;
	vec3(0, 0, 5, camera_pos);
	vec3(0, 0, -1, camera_dir);
	vec3(u - 0.5f, v - 0.5f, 4, pixel_pos); // u/v: -0.5 -> +0.5
	vec3_copy(camera_pos, ray.origin); // ray.origin = camera_pos
	vec3_sub(pixel_pos, camera_pos, ray.direction);
	t = hit_sphere(ray, sphere);
	if (t > 0.f)
	{
		ray_at(ray, t, normal);
		// - 0,0,-1
		vec3_sub(normal, vec3(0, 0, 0, tmp), normal);
		// normalize
		vec3_normalize(normal, normal);
		// printf("hit at: (%f, %f, %f)\n", normal[0], normal[1], normal[2]);
		color = get_color((normal[0] + 1.f) * 127, (normal[1] + 1.f) * 127, (normal[2] + 1.f) * 127, 0);
	}
	else
		color = get_color(0, u * 255, v * 255, 0);
	return (color);
}

void	*fill_img(void *img)
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
		px_coord.x = 0;
		while (px_coord.x < WIDTH)
		{
			pixel_addr = (px_coord.y * img_info.line_size) + (px_coord.x * 4);
			color = choose_color(
				(px_coord.x / (float)WIDTH),
				(px_coord.y / (float)HEIGHT));
			write_pixel(buffer, pixel_addr, color, img_info.endian);
			px_coord.x++;
		}
		px_coord.y++;
	}
	return (img);
}

int	main(void)
{
	int		window_height;
	int		window_width;
	t_data	data;

	window_height = HEIGHT;
	window_width = WIDTH;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, window_width, window_height, "miniRT");
	data.img = mlx_new_image(data.mlx, window_width, window_height);
	mlx_put_image_to_window(data.mlx, data.win, fill_img(data.img), 0, 0);
	mlx_hook(data.win, 17, (1L << 17), &close_window, &data);
	mlx_key_hook(data.win, &key_hook, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
