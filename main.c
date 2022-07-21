/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:28 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/21 12:42:28 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

struct s_data
{
	void	*mlx;
	void	*win;
};
typedef struct s_data t_data;

static int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	//mlx_destroy_display(data->mlx_ptr);
	//free(data->mlx_ptr); // if active, it causes mem leaks on MacOS?!
	system("leaks mini_rt");
	exit(0);
	return (0);
}

int	main(void)
{
	const int	window_height = 400;
	const int	window_width = 400;
	t_data		data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, window_width, window_height, "miniRT");

	mlx_hook(data.win, 17, (1L << 17), &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
