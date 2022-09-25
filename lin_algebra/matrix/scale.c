/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:28:40 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/20 12:35:51 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

/*
4x4 scaling matrix
x 0 0 0
0 y 0 0
0 0 z 0
0 0 0 1
*/
float	*mat4_scale(float x, float y, float z, float *result)
{
	size_t	i;

	result[0] = x;
	i = 1;
	while (i < MAT4_SIZE)
	{
		if (i == 5)
			result[i] = y;
		else if (i == 10)
			result[i] = z;
		else if (i == 15)
			result[i] = 1;
		else
			result[i] = 0;
		i++;
	}
	return (result);
}
