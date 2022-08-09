/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:26:36 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/08 14:14:16 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_obj	*new_object(float pos[VEC3_SIZE], int color)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		exit_fatal();
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
		destroy_sphere((t_sphere *) obj->specifics);
	else if (obj->type == LIGHT)
		free((t_light *) obj->specifics);
	else
		ft_error(1, "destroy_object: unkon object type.");

	free(obj);
}
