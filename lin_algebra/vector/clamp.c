/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:52:13 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/29 20:22:39 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float	*vec3_clamp(float *vec, float lower, float upper, float *result)
{
	result[0] = fmaxf(lower, fminf(vec[0], upper));
	result[1] = fmaxf(lower, fminf(vec[1], upper));
	result[2] = fmaxf(lower, fminf(vec[2], upper));
	return (result);
}
