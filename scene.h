/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:28:53 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 21:28:36 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "matrix.h"
# include "libft.h"
# include "ray.h"

enum e_obj_type
{
	NONE,
	SPHERE,
	CYLINDER,
	PLANE,
	LIGHT
};

struct s_transform
{
	float	forward[MAT4_SIZE];
	float	backward[MAT4_SIZE];
};
typedef struct s_transform	t_tform;

typedef struct s_amlight {
	float	ratio;
	float	color[VEC3_SIZE];
}	t_amlight;

typedef struct s_camera {
	float	pos[3];
	float	ovector[3];
	float	fov;
	t_tform	transform;
}	t_camera;

typedef struct s_light {
	float	brightness;
}	t_light;

typedef struct s_sphere {
	float	diameter;
}	t_sphere;

typedef struct s_plane {
	float	ovector[3];
}	t_plane;

typedef struct s_cylinder {
	float	ovector[3];
	float	diameter;
	float	height;
}	t_cylinder;

// (cylinder) helper structs to only use four parameters and five variables

struct s_dimension {
	float	diameter;
	float	height;
};

typedef struct s_cylinder_info {
	float				pos[VEC3_SIZE];
	float				color[VEC3_SIZE];
	float				orientation[VEC3_SIZE];
	struct s_dimension	dimension;
}							t_cylinder_info;

struct s_cyl_intersect
{
	float			t_values[4];
	float			intersection[VEC3_SIZE];
	bool			valid[4];
	int				min_index;
	struct s_ray	*ray;
};

typedef struct s_obj {
	float	pos[VEC3_SIZE];
	t_tform	transform;
	float	color[VEC3_SIZE];
	int		type;
	void	*specifics;
}	t_obj;

struct s_scene
{
	t_amlight	*ambient_light;
	t_obj		*light;
	t_camera	*camera;
	int			obj_count;
	t_list		*objects;
};
typedef struct s_scene		t_scene;

//	scene.c
t_scene		*new_scene(void);
void		destroy_scene(t_scene *scene);
bool		add_obj_to_scene(t_scene *scene, t_obj *obj);
t_obj		*get_obj_from_scene(t_scene *scene, int index);

//	object.c
t_obj		*new_object(float pos[VEC3_SIZE], float color[VEC3_SIZE]);
void		destroy_object(t_obj *obj);

//	camera.c
t_camera	*new_camera(float pos[VEC3_SIZE], float dir[VEC3_SIZE], float fov);

//	light.c
t_amlight	*new_ambient_light(float ratio, float color[VEC3_SIZE]);
t_obj		*new_light(float pos[VEC3_SIZE], float color[VEC3_SIZE], \
			float brightness);

//	sphere.c
t_obj		*new_sphere(float pos[VEC3_SIZE], float color[VEC3_SIZE], \
			float diameter);
bool		hit_sphere(struct s_ray ray, t_obj *sphere, float point[VEC3_SIZE], \
			float local_normal[VEC3_SIZE]);

//	plane.c
t_obj		*new_plane(float pos[VEC3_SIZE], float color[VEC3_SIZE], \
			float dir[VEC3_SIZE]);
bool		hit_plane(struct s_ray ray, t_obj *plane, float point[VEC3_SIZE], \
			float local_normal[VEC3_SIZE]);

//	cylinder.c
t_obj		*new_cylinder(float pos[VEC3_SIZE], float color[VEC3_SIZE], \
			float orientation[VEC3_SIZE], struct s_dimension dim);
bool		hit_cylinder(struct s_ray ray, t_obj *cylinder, \
			float point[VEC3_SIZE], float local_normal[VEC3_SIZE]);
bool		close_enough(float a, float b);

//	cylinder_intersection.c

int			find_closest_intersect(struct s_cyl_intersect *data,
				float point[VEC3_SIZE]);
void		wall_intersect(float a, float b, float c,
				struct s_cyl_intersect *data);
void		cap_intersect(struct s_cyl_intersect *data);
void		normal_wall(t_obj *cyl, float point[VEC3_SIZE],
				float normal[VEC3_SIZE]);
void		normal_cap(t_obj *cyl, float point[VEC3_SIZE],
				float normal[VEC3_SIZE]);

#endif
