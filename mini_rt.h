/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:12:46 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/05 17:09:34 by chelmerd         ###   ########.fr       */
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

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define WHITE 0x00FFFFFF

# define MIN_RATIO 0.f
# define MAX_RATIO 1.f

# define MAX_UNIT_VECTOR_COMP 1.f
# define MIN_UNIT_VECTOR_COMP -(MAX_UNIT_VECTOR_COMP)

# define MIN_COLOR_VALUE 0
# define MAX_COLOR_VALUE 255

# define MIN_FOV 0
# define MAX_FOV 180

enum e_obj_type
{
	NONE,
	SPHERE,
	CYLINDER,
	PLANE,
	LIGHT
};

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

// struct					s_sphere
// {
// 	float		center[VEC3_SIZE];
// 	float				radius;
// 	// s_vec4	color;
// 	unsigned			color;
// };

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

typedef struct s_sphere {
	float	diameter;
}t_sphere;

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
	int		type;
	void	*specifics;
}t_obj;

t_obj	*new_object(float pos[VEC3_SIZE], int color);
void	destroy_object(t_obj *obj);

t_amlight	*new_ambient_light(float ratio, int color);
t_obj		*new_light(float pos[VEC3_SIZE], int color, float brightness);
t_camera	*new_camera(float pos[VEC3_SIZE], float ovector[VEC3_SIZE], int fov);

t_obj	*new_sphere(float pos[VEC3_SIZE], int color, float diameter);

//	check_file.c
int	checkfile(char *path);

// scene

// screen (depends on camera FOV, aspect ratio and resolution)
// struct s_screen
// {
// 	float		aspect_ratio;
// 	unsigned	width;
// 	unsigned	height;
// };
// typedef struct s_screen t_screen;

struct s_scene
{
	t_amlight	*ambient_light;
	t_obj		*light;
	t_camera	*camera;
	// t_screen	screen;
	size_t		obj_count; // or: NULL-terminate the object array
	t_obj		**objects; // array of pointer to objects to render
};
typedef struct s_scene t_scene;

t_scene	*new_scene(t_amlight *ambient_light, t_obj *light, t_camera *camera);
void	destroy_scene(t_scene *scene);

// util

void	exit_fatal(void);

#endif
