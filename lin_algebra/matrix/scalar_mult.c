/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:20:29 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/14 20:02:52 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

float	*mat4_scalar_mult(float *m, float s, float *result)
{
	size_t	i;

	i = 0;
	while (i < MAT4_SIZE)
		m[i++] *= s;
	i = 0;
	while (i < MAT4_SIZE)
	{
		result[i] = m[i];
		i++;
	}
	return (result);
}
