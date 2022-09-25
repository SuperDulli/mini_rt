/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:16:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/26 13:19:02 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	*vec2_copy(float *vec, float *result)
{
	result[0] = vec[0];
	result[1] = vec[1];
	return (result);
}

float	*vec3_copy(float *vec, float *result)
{
	result[0] = vec[0];
	result[1] = vec[1];
	result[2] = vec[2];
	return (result);
}

float	*vec4_copy(float *vec, float *result)
{
	result[0] = vec[0];
	result[1] = vec[1];
	result[2] = vec[2];
	result[3] = vec[3];
	return (result);
}
