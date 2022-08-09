/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:20:54 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/09 12:21:04 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
