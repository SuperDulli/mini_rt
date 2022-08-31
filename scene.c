/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:27:49 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/30 15:19:05 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_scene	*new_scene(void)
{
	t_scene	*scene;

	scene = new(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->ambient_light = NULL;
	scene->light = NULL;
	scene->camera = NULL;
	scene->obj_count = 0;
	scene->objects = NULL;
	return (scene);
}

void	delete_obj_list_item(void *item)
{
	t_obj	*obj;

	obj = (t_obj *) item;
	destroy_object(obj);
}

void	destroy_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->ambient_light)
		free(scene->ambient_light);
	if (scene->camera)
		free(scene->camera);
	destroy_object(scene->light);
	ft_lstclear(&scene->objects, delete_obj_list_item);
	free(scene);
}

bool	add_obj_to_scene(t_scene *scene, t_obj *obj)
{
	t_list	*elem;

	if (!scene || !obj)
	{
		ft_error(1, "add_obj_to_scene: object or scene is a NULL-Pointer.");
		return (false);
	}
	elem = ft_lstnew(obj);
	if (!elem)
	{
		ft_error(2, "add_obj_to_scene: cannnot put object into the list.");
		return (false);
	}
	ft_lstadd_back(&scene->objects, elem);
	scene->obj_count++;
	return (true);
}

t_obj	*get_obj_from_scene(t_scene * scene, int index)
{
	t_obj	*obj;
	t_list	*tmp;
	int		i;

	if (index < 0 || index > scene->obj_count)
	{
		ft_error(1, "get_obj_from_scene: index not in range.");
		return (NULL);
	}
	tmp = scene->objects;
	i = 0;
	while (i < index)
	{
		i++;
		tmp = tmp->next;
	}
	obj = (t_obj *) tmp->content;
	return (obj);
}

t_scene	*build_scene(void)
{
	t_scene		*scene;
	t_amlight	*ambient;
	t_obj		*light;
	t_camera	*camera;
	float		pos[VEC3_SIZE];
	float		dir[VEC3_SIZE];

	// debug values
	ambient = new_ambient_light(0.5f, WHITE);
	// far away light source creates light rays that are "more" parallel
	light = new_light(vec3(3,3,5, pos), WHITE, 0.5f);
	camera = new_camera(vec3(0, 0, 3, pos), vec3(0, 0, -1, dir), 90);
	scene = new_scene();
	if (!ambient || !light || !camera || !scene)
	{
		ft_error(1, "build_scene: cannnot create create scene.");
		return (NULL);
	}
	scene->ambient_light = ambient;
	scene->light = light;
	scene->camera = camera;

	// just add one unit cylinder (centerd at the origin) for now
	// scene->objects = malloc(sizeof(t_obj *) * 1);
	if (!add_obj_to_scene(scene, new_cylinder(vec3(0,0,0, pos), BLUE, vec3(0.f,1.f,0.f, dir), 2.f, 2.f)))
	{
		ft_error(2, "build_scene: cannot add obj to scene.");
		destroy_scene(scene);
		return (NULL);
	}
	return (scene);
}
