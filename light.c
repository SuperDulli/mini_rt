/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:20:54 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/04 16:23:21 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_amlight	*new_ambient_light(float ratio, float color[VEC3_SIZE])
{
	t_amlight	*ambient;

	ambient = new(sizeof(t_amlight));
	if (!ambient)
		return (NULL);
	ambient->ratio = ratio;
	ambient->color[0] = color[0];
	ambient->color[1] = color[1];
	ambient->color[2] = color[2];
	return (ambient);
}

t_obj	*new_light(float pos[VEC3_SIZE], float color[VEC3_SIZE], float brightness)
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
