/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:36:18 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/13 16:37:28 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	*vec2_scalar_mult(float *v, float s, float *result)
{
	result[0] = v[0] * s;
	result[1] = v[1] * s;
	return (result);
}

float	*vec3_scalar_mult(float *v, float s, float *result)
{
	result[0] = v[0] * s;
	result[1] = v[1] * s;
	result[2] = v[2] * s;
	return (result);
}

float	*vec4_scalar_mult(float *v, float s, float *result)
{
	result[0] = v[0] * s;
	result[1] = v[1] * s;
	result[2] = v[2] * s;
	result[3] = v[3] * s;
	return (result);
}
