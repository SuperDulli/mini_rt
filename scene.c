/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:27:49 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/05 15:06:21 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	*new(size_t size)
{
	void	*n;

	n = malloc(size);
	if (!n)
		exit_fatal();
	return (n);
}

t_scene	*new_scene(t_amlight *ambient_light, t_obj *light, t_camera *camera)
{
	t_scene	*scene;

	// sanity check
	if (!ambient_light || !light || !camera)
	{
		ft_error(1, "new_scene: mandatory component not set (NULL-pointer).");
	}

	// scene = malloc(sizeof(t_scene));
	// if (!scene)
	// 	exit_fatal();
	scene = (t_scene *) new(sizeof(t_scene));
	scene->ambient_light = ambient_light;
	scene->light = light;
	scene->camera = camera;
	scene->obj_count = 0;
	scene->objects = NULL;
	return (scene);
}

void	destroy_scene(t_scene *scene)
{
	size_t	i;

	if (!scene)
		return ;
	free(scene->ambient_light);
	destroy_object(scene->light);
	free(scene->camera);
	i = 0;
	while (i < scene->obj_count)
	{
		destroy_object(scene->objects[i++]);
	}
	free(scene->objects);
	free(scene);
}

t_amlight	*new_ambient_light(float ratio, int color)
{
	t_amlight	*ambient;

	ambient = (t_amlight *) new(sizeof(t_amlight));
	ambient->ratio = ratio;
	ambient->color = color;
	return (ambient);
}

t_obj	*new_light(float pos[VEC3_SIZE], int color, float brightness)
{
	t_obj	*obj;
	t_light	*light;

	obj = new_object(pos, color);
	obj->type = LIGHT;
	light = (t_light *) new(sizeof(t_light));
	light->brightness = brightness;
	obj->specifics = light;
	return (obj);
}

t_camera	*new_camera(float pos[VEC3_SIZE], float ovector[VEC3_SIZE], int fov)
{
	t_camera	*camera;

	camera = (t_camera *) new(sizeof(t_camera));
	camera->pos[0] = pos[0];
	camera->pos[1] = pos[1];
	camera->pos[2] = pos[2];
	camera->ovector[0] = ovector[0];
	camera->ovector[1] = ovector[1];
	camera->ovector[2] = ovector[2];
	camera->fov = fov;
	return (camera);
}

void	add_obj_to_scene(t_scene *scene, t_obj *obj)
{
	if (!scene || !obj)
	{
		ft_error(1, "add_obj_to_scene: cannot add object.");
		return ;
	}
	scene->objects[scene->obj_count] = obj;
	scene->obj_count++;
}

t_scene	*build_scene(void)
{
	t_scene		*scene;
	t_amlight	*ambient;
	t_obj		*obj;
	t_camera	*camera;
	float		pos[VEC3_SIZE];
	float		dir[VEC3_SIZE];

	// debug values
	ambient = new_ambient_light(MAX_RATIO, WHITE);
	obj = new_light(vec3(5, 5, 5, pos), WHITE, MAX_RATIO);
	camera = new_camera(vec3(0, 0, 5, pos), vec3(0, 0, -1, dir), 90);
	scene = new_scene(ambient, obj, camera);

	// just add one unit sphere (centerd at the origin) for now
	scene->objects = malloc(sizeof(t_obj *) * 1);
	add_obj_to_scene(scene, new_sphere(vec3(0, 0, 0, pos), BLUE, 2.f));
	return (scene);
}
