/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:27:49 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/04 16:17:24 by chelmerd         ###   ########.fr       */
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

t_obj	*get_obj_from_scene(t_scene *scene, int index)
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
