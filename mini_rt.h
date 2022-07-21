/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:12:46 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/21 15:22:22 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "mlx.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define HEIGHT 900
# define WIDTH 1600

struct					s_data
{
	void				*mlx;
	void				*win;
	void				*img;
};
typedef struct s_data	t_data;

struct s_img_info
{
	int	bits_per_pixel;
	int	line_size;
	int	endian;
};

struct s_2d_coord
{
	int	x;
	int	y;
};


#endif
