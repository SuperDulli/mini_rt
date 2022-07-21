/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:28 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/21 15:29:14 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	//mlx_destroy_display(data->mlx_ptr);
	//free(data->mlx_ptr); // if active, it causes mem leaks on MacOS?!
	system("leaks mini_rt");
	exit(0);
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
			color = get_color(0, (px_coord.x / (float)WIDTH) * 255, (px_coord.y
						/ (float)HEIGHT) * 255, 0);
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
	mlx_loop(data.mlx);
	return (0);
}
