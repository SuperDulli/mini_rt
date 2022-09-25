/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_squared.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:26:54 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/13 16:29:13 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	vec2_length_squared(float *v)
{
	return (v[0] * v[0] + v[1] * v[1]);
}

float	vec3_length_squared(float *v)
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float	vec4_length_squared(float *v)
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}
