/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:20:54 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/30 12:20:51 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_amlight	*new_ambient_light(float ratio, int color)
{
	t_amlight	*ambient;

	ambient = new(sizeof(t_amlight));
	if (!ambient)
		return (NULL);
	ambient->ratio = ratio;
	ambient->color = color;
	return (ambient);
}

t_obj	*new_light(float pos[VEC3_SIZE], int color, float brightness)
{
	t_obj	*obj;
	t_light	*light;

	obj = new_object(pos, color);
	if (!obj)
		return (NULL);
	obj->specifics = new(sizeof(t_light));
	if (!obj->specifics)
	{
		destroy_object(obj);
		return (NULL);
	}
	obj->type = LIGHT;
	light = (t_light *) obj->specifics;
	light->brightness = brightness;
	return (obj);
}
