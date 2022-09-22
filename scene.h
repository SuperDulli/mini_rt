/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:28:53 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/08 14:25:27 by chelmerd         ###   ########.fr       */
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

typedef struct s_obj {
	float	pos[VEC3_SIZE];
	t_tform	transform;
	float 	color[VEC3_SIZE];
	int		type;
	void	*specifics;
}	t_obj;

struct s_scene
{
	t_amlight	*ambient_light;
	t_obj		*light;
	t_camera	*camera;
	int			obj_count;
	t_list		*objects; // list of pointer to objects to render
};
typedef struct s_scene		t_scene;

// scene

t_scene		*new_scene(void);
void		destroy_scene(t_scene *scene);
bool		add_obj_to_scene(t_scene *scene, t_obj *obj);
t_obj		*get_obj_from_scene(t_scene *scene, int index);

// object

t_obj		*new_object(float pos[VEC3_SIZE], float color[VEC3_SIZE]);
void		destroy_object(t_obj *obj);

// camera

t_camera	*new_camera(float pos[VEC3_SIZE], float dir[VEC3_SIZE], float fov);

// light

t_amlight	*new_ambient_light(float ratio, float color[VEC3_SIZE]);
t_obj		*new_light(float pos[VEC3_SIZE], float color[VEC3_SIZE], float brightness);

// sphere

t_obj		*new_sphere(float pos[VEC3_SIZE], float color[VEC3_SIZE], float diameter);
bool		hit_sphere(struct s_ray ray, t_obj *sphere, float point[VEC3_SIZE], float local_normal[VEC3_SIZE]);

// plane

t_obj		*new_plane(float pos[VEC3_SIZE], float color[VEC3_SIZE], float dir[VEC3_SIZE]);
bool		hit_plane(struct s_ray ray, t_obj *plane, float point[VEC3_SIZE], float local_normal[VEC3_SIZE]);

// cylinder

t_obj		*new_cylinder(
				float pos[VEC3_SIZE],
				float color[VEC3_SIZE],
				float orientation[VEC3_SIZE],
				float diameter,
				float height
				);
bool		hit_cylinder(struct s_ray ray, t_obj *cylinder, float point[VEC3_SIZE], float local_normal[VEC3_SIZE]);

#endif
