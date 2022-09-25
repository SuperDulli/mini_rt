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
		while (px_coord.x < WIDTH)
		{
			pixel_addr = (px_coord.y * img_info.line_size) + (px_coord.x * 4);
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
