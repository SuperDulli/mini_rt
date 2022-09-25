/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:29:19 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/13 16:32:05 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float	vec2_length(float *v)
{
	return (sqrtf(v[0] * v[0] + v[1] * v[1]));
}

float	vec3_length(float *v)
{
	return (sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

float	vec4_length(float *v)
{
	return (sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]));
}
