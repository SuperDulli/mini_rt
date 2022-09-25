/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:31:39 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/13 17:04:42 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float	*vec2_normalize(float *v, float *result)
{
	const float	len = sqrtf(v[0] * v[0] + v[1] * v[1]);

	result[0] = v[0] / len;
	result[1] = v[1] / len;
	return (result);
}

float	*vec3_normalize(float *v, float *result)
{
	const float	len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

	result[0] = v[0] / len;
	result[1] = v[1] / len;
	result[2] = v[2] / len;
	return (result);
}

float	*vec4_normalize(float *v, float *result)
{
	const float	len
		= sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);

	result[0] = v[0] / len;
	result[1] = v[1] / len;
	result[2] = v[2] / len;
	result[3] = v[3] / len;
	return (result);
}
