/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:12:46 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/31 18:52:36 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "matrix.h"
# include "mlx.h"
# include "vector.h"
# include "libft.h"
# include "keys.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>

# define HEIGHT 800
# define WIDTH 800

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

# define MIN_RATIO 0.f
# define MAX_RATIO 1.f

# define MAX_UNIT_VECTOR_COMP 1.f
# define MIN_UNIT_VECTOR_COMP -(MAX_UNIT_VECTOR_COMP)

# define MIN_COLOR_VALUE 0
# define MAX_COLOR_VALUE 255

# define MIN_FOV 0
# define MAX_FOV 180

# define MAX_FLOAT 2000
# define MAX_PRECISION 4

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

struct s_transform
{
	float	forward[MAT4_SIZE];
	float	backward[MAT4_SIZE];
};
typedef	struct s_transform t_tform; // read: type transform

typedef struct s_obj {
	float	pos[VEC3_SIZE];
	t_tform	transform;
	int		colourcode;
	int		type;
	void	*specifics;
}t_obj;

struct s_scene
{
	t_amlight	*ambient_light;
	t_obj		*light;
	t_camera	*camera;
	// t_screen	screen;
	int		obj_count; // or: NULL-terminate the object array
	t_list		*objects; // array of pointer to objects to render
};
typedef struct s_scene t_scene;

t_obj	*new_object(float pos[VEC3_SIZE], int color);
void	destroy_object(t_obj *obj);

t_amlight	*new_ambient_light(float ratio, int color);
t_obj		*new_light(float pos[VEC3_SIZE], int color, float brightness);
t_camera	*new_camera(float pos[VEC3_SIZE], float ovector[VEC3_SIZE], int fov);

// sphere

t_obj	*new_sphere(float pos[VEC3_SIZE], int color, float diameter);

// camera

t_camera	*new_camera(float pos[VEC3_SIZE], float ovector[VEC3_SIZE], int fov);

// light

t_amlight	*new_ambient_light(float ratio, int color);
t_obj	*new_light(float pos[VEC3_SIZE], int color, float brightness);

// plane

t_obj	*new_plane(float pos[VEC3_SIZE], int color, float orientation[VEC3_SIZE]);

// cylinder

t_obj	*new_cylinder(
	float pos[VEC3_SIZE],
	int color,
	float orientation[VEC3_SIZE],
	float diameter,
	float height
);

//	check_file.c
int		checkfile(char *path);
int		readfile(int fd);
int		checkline(char *line, char *duplicate);
int		check_cylinder(char *line);
void	readfile_helper(char *line, int fd, int *err);

//	check_elements.c
int check_amlight(char *line, char *duplicate);
int	check_camera(char *line, char *duplicate);
int	check_light(char *line, char *duplicate);
int	check_sphere(char *line);
int	check_plane(char *line);

//	check_utils.c
int		arr_size(char **arr);
void	arr_free(char **arr);
void	replace_tabs(char *line);
float	ft_atof(const char *str);
int		check_string_range(char *str, int min, int max);

//	check_info.c
int	check_color(char *color);
int	check_int(char *info);
int	check_float(char *info);
int	check_vector(char *argument);
int	check_vector_range(char *argument, int min, int max);

//store_data.c
int		store_data(char *path, t_scene	*scene);
int		save_data(char *line, t_scene *scene);
void	get_data(char *line, int fd, int *err, t_scene *scene);
// int		save_cylinder(char *line, t_scene *scene);

//store_elements.c
int	save_amlight(char *line, t_scene *scene);
int	save_camera(char *line, t_scene *scene);
int save_light(char *line, t_scene *scene);
int	save_sphere(char *line, t_scene *scene);
// int save_plane(char *line, t_scene *scene);

//store_utils.c
int	str_to_vec(char *info, float *vec);
// int	str_to_color(char *info);

// util

void	exit_fatal(void);
void	*new(size_t size);

// ray

float	*ray_at(struct s_ray ray, float t, float *point);

// color

int				get_red(int color);
int				get_green(int color);
int				get_blue(int color);
unsigned int	get_color(unsigned alpha, unsigned r, unsigned g, unsigned b);
float			*color_vec(int red, int green, int blue, float *result);
float			*color_vec_from_int(int argb, float *result);
int				convert_to_argb(float rgb[VEC3_SIZE]);

// scene

// screen (depends on camera FOV, aspect ratio and resolution)
// struct s_screen
// {
// 	float		aspect_ratio;
// 	unsigned	width;
// 	unsigned	height;
// };
// typedef struct s_screen t_screen;

t_scene	*new_scene(void);
void	destroy_scene(t_scene *scene);
bool	add_obj_to_scene(t_scene *scene, t_obj *obj);
t_obj	*get_obj_from_scene(t_scene * scene, int index);

// transform

void	set_transform(
	float transl[VEC3_SIZE],
	float rotation[VEC3_SIZE],
	float scale[VEC3_SIZE],
	t_tform *transform
);
float	*apply_transform(float vec[VEC3_SIZE], float transf[MAT4_SIZE], int is_point, float *result);

#endif
