/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:27:06 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 17:11:20 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.h"
#include <stdio.h>

float	*vec_fill(float value, size_t len, float *result)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		result[i] = value;
		i++;
	}
	return (result);
}

float	*vec2(float x, float y, float *result)
{
	result[0] = x;
	result[1] = y;
	return (result);
}

float	*vec3(float x, float y, float z, float *result)
{
	result[0] = x;
	result[1] = y;
	result[2] = z;
	return (result);
}

// norm only allows function that take a maximum of 4 parameters

struct s_quad	tuple4(float x, float y, float z, float w)
{
	struct s_quad	t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = w;
	return (t);
}

float	*vec4(struct s_quad values, float *result)
{
	result[0] = values.x;
	result[1] = values.y;
	result[2] = values.z;
	result[3] = values.w;
	return (result);
}
