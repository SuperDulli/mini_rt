/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:27:49 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/17 14:41:34 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	ambient = new_ambient_light(0.5f, WHITE);

	// far away light source creates light rays that are "more" parallel
	obj = new_light(vec3(900,900,-900, pos), WHITE, 0.5f);
	camera = new_camera(vec3(0, 0, 3, pos), vec3(0, 0, -1, dir), 90);
	scene = new_scene(ambient, obj, camera);

	// just add one unit cylinder (centerd at the origin) for now
	scene->objects = malloc(sizeof(t_obj *) * 1);
	add_obj_to_scene(scene, new_cylinder(vec3(0,0,0, pos), BLUE, vec3(0.f,1.f,0.f, dir), 2.f, 2.f));
	return (scene);
}
