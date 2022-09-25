/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:23:15 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/01 12:43:46 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.h"

/**
* @brief maps a vec from [-1, 1] to [0, 1]
*
* @param vec an 3-component vector (float array)
* @param result vector to store the mapped values
* @return float* - address of result
*/
float	*vec3_shift_positive(float *vec, float *result)
{
	vec3_scalar_mult(vec, 0.5f, result);
	vec3(result[0] + 0.5f, result[1] + 0.5f, result[2] + 0.5f, result);
	return (result);
}
