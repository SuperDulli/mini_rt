/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:28:53 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/01 11:41:53 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "matrix.h"
# include "libft.h"

enum e_obj_type
{
	NONE,
	SPHERE,
	CYLINDER,
	PLANE,
	LIGHT
};

typedef struct s_amlight {
	float	ratio;
	int		color;
}	t_amlight;

typedef struct s_camera {
	float	pos[3];
	float	ovector[3];
	int		fov;			// float??
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

struct s_transform
{
	float	forward[MAT4_SIZE];
	float	backward[MAT4_SIZE];
};
typedef struct s_transform	t_tform;

typedef struct s_obj {
	float	pos[VEC3_SIZE];
	t_tform	transform;
	int		colourcode;
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

t_obj		*new_object(float pos[VEC3_SIZE], int color);
void		destroy_object(t_obj *obj);

// camera

t_camera	*new_camera(float pos[VEC3_SIZE], float dir[VEC3_SIZE], int fov);

// light

t_amlight	*new_ambient_light(float ratio, int color);
t_obj		*new_light(float pos[VEC3_SIZE], int color, float brightness);

// sphere

t_obj		*new_sphere(float pos[VEC3_SIZE], int color, float diameter);

// plane

t_obj		*new_plane(float pos[VEC3_SIZE], int color, float dir[VEC3_SIZE]);

// cylinder

t_obj		*new_cylinder(
				float pos[VEC3_SIZE],
				int color,
				float orientation[VEC3_SIZE],
				float diameter,
				float height
				);

#endif
