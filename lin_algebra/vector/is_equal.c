/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_equal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:19:00 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/13 16:26:35 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include <stdbool.h>

bool	vec2_is_equal(float *v1, float *v2)
{
	return (fabsf(v1[0] - v2[0]) < FLT_EPSILON
		&& fabsf(v1[1] - v2[1]) < FLT_EPSILON);
}

bool	vec3_is_equal(float *v1, float *v2)
{
	return (fabsf(v1[0] - v2[0]) < FLT_EPSILON
		&& fabsf(v1[1] - v2[1]) < FLT_EPSILON
		&& fabsf(v1[2] - v2[2]) < FLT_EPSILON);
}

bool	vec4_is_equal(float *v1, float *v2)
{
	return (fabsf(v1[0] - v2[0]) < FLT_EPSILON
		&& fabsf(v1[1] - v2[1]) < FLT_EPSILON
		&& fabsf(v1[2] - v2[2]) < FLT_EPSILON
		&& fabsf(v1[3] - v2[3]) < FLT_EPSILON);
}
