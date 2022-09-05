/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:26:36 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/04 16:29:40 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_obj	*new_object(float pos[VEC3_SIZE], float color[VEC3_SIZE])
{
	t_obj	*obj;

	obj = new(sizeof(t_obj));
	if (!obj)
	{
		return (NULL);
	}
	obj->type = NONE;
	obj->specifics = NULL;
	obj->color[0] = color[0];
	obj->color[1] = color[1];
	obj->color[2] = color[2];
	obj->pos[0] = pos[0];
	obj->pos[1] = pos[1];
	obj->pos[2] = pos[2];
	mat4_zero(obj->transform.forward);
	mat4_zero(obj->transform.backward);

	return (obj);
}

void	destroy_object(t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->type == SPHERE)
		free((t_sphere *) obj->specifics);
	else if (obj->type == LIGHT)
		free((t_light *) obj->specifics);
	else if (obj->type == CYLINDER)
		free((t_cylinder *) obj->specifics);
	else if (obj->type == PLANE)
		free((t_plane *) obj->specifics);
	else
		ft_error(1, "destroy_object: unkown object type.");

	free(obj);
}
