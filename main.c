/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:28 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/21 13:45:37 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

#define HEIGHT 400
#define WIDTH 400

struct					s_data
{
	void				*mlx;
	void				*win;
	void				*img;
};
typedef struct s_data	t_data;

static int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	//mlx_destroy_display(data->mlx_ptr);
	//free(data->mlx_ptr); // if active, it causes mem leaks on MacOS?!
	// system("leaks mini_rt");
	exit(0);
	return (0);
}

void	*fill_img(void *img)
{
	int	color;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*buffer;
	int			x;
	int			y;
	int			pixel;

	color = 0xABCDEF;
	buffer = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = (y * size_line) + (x * 4);
			if (endian == 1) // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color >> 24);
				buffer[pixel + 1] = (color >> 16) & 0xFF;
				buffer[pixel + 2] = (color >> 8) & 0xFF;
				buffer[pixel + 3] = (color)&0xFF;
			}
			else if (endian == 0) // Least significant (Blue) byte first
			{
				buffer[pixel + 0] = 0x00;
				buffer[pixel + 1] = (y / (float) HEIGHT) * 0xFF;
				buffer[pixel + 2] =	(x / (float) WIDTH) * 0xFF;
				buffer[pixel + 3] = 0x00;
				// buffer[pixel + 0] = (color)&0xFF;
				// buffer[pixel + 1] = (color >> 8) & 0xFF;
				// buffer[pixel + 2] = (color >> 16) & 0xFF;
				// buffer[pixel + 3] = (color >> 24);
			}
			x++;
		}
		y++;
	}
	return (img);
}

int	main(void)
{
	int	window_height;
	int	window_width;
	t_data		data;

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
