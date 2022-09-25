/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:15:07 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/21 16:49:08 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	*vec2_add(float *v1, float *v2, float *result)
{
	result[0] = v1[0] + v2[0];
	result[1] = v1[1] + v2[1];
	return (result);
}

float	*vec3_add(float *v1, float *v2, float *result)
{
	result[0] = v1[0] + v2[0];
	result[1] = v1[1] + v2[1];
	result[2] = v1[2] + v2[2];
	return (result);
}

float	*vec4_add(float *v1, float *v2, float *result)
{
	result[0] = v1[0] + v2[0];
	result[1] = v1[1] + v2[1];
	result[2] = v1[2] + v2[2];
	result[3] = v1[3] + v2[3];
	return (result);
}
