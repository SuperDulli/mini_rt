/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:12:46 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/23 15:46:01 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "matrix.h"
# include "mlx.h"
# include "vector.h"
# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
// # include <string.h>
# include <fcntl.h>

# define HEIGHT 800
# define WIDTH 800

struct					s_data
{
	void				*mlx;
	void				*win;
	void				*img;
};
typedef struct s_data	t_data;

struct					s_img_info
{
	int					bits_per_pixel;
	int					line_size;
	int					endian;
};

struct					s_2d_coord
{
	int					x;
	int					y;
};

struct					s_sphere
{
	float		center[VEC3_SIZE];
	float				radius;
	// s_vec4	color;
	unsigned			color;
};

struct s_ray
{
	float	origin[VEC3_SIZE];
	float	direction[VEC3_SIZE];
};

typedef struct s_amlight {
	float	ratio;
	int		color;
}t_amlight;

typedef struct s_camera {
	float	pos[3];
	float	ovector[3];
	int		fov;			// float??
}t_camera;

typedef	struct s_light {
	float	brightness;
}t_light;

// typedef struct s_sphere {
// 	float	diameter;
// }t_sphere;

typedef struct s_plane {
	float	ovector[3];
}t_plane;

typedef struct s_cylinder {
	float	ovector[3];
	float	diameter;
	float	height;	
}t_cylinder;

typedef struct s_obj {
	float	pos[3];
	int		colourcode;	// farbwerte einzeln?
	int		typ;
	void	*specifics;
}t_obj;

//	check_file.c
int	checkfile(char *path);
int	readfile(int fd);
int	checkline(char *line);

//	check_elements.c
int check_amlight(char *line);
int	check_camera(char *line);

//	check_utils.c
int		arr_size(char **arr);
void	arr_free(char **arr);
void	replace_tabs(char *line);
int		check_float(char *info);
float	ft_atof(const char *str);

//	check_info.c
int	check_color(char *color);
int	check_int(char *info);
int	check_vector(char **vector);

#endif
