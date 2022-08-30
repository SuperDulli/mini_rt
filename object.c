/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:26:36 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/30 12:40:50 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_obj	*new_object(float pos[VEC3_SIZE], int color)
{
	t_obj	*obj;

	obj = new(sizeof(t_obj));
	if (!obj)
	{
		return (NULL);
	}
	obj->type = NONE;
	obj->specifics = NULL;
	obj->colourcode = color;
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
	else
		ft_error(1, "destroy_object: unkown object type.");

	free(obj);
}
