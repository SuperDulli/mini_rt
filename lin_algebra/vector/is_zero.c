/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_zero.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:22:39 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/13 16:26:16 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include <stdbool.h>

bool	vec2_is_zero(float *vec)
{
	return (fabsf(vec[0]) < FLT_EPSILON
		&& fabsf(vec[1]) < FLT_EPSILON);
}

bool	vec3_is_zero(float *vec)
{
	return (fabsf(vec[0]) < FLT_EPSILON
		&& fabsf(vec[1]) < FLT_EPSILON
		&& fabsf(vec[2]) < FLT_EPSILON);
}

bool	vec4_is_zero(float *vec)
{
	return (fabsf(vec[0]) < FLT_EPSILON
		&& fabsf(vec[1]) < FLT_EPSILON
		&& fabsf(vec[2]) < FLT_EPSILON
		&& fabsf(vec[3]) < FLT_EPSILON);
}
