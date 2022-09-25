/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:39:09 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/20 12:59:53 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

/*
4x4 rotating matrix (x-axis)
1		0		0		0
0		cosθ	-sinθ	0
0		sinθ	cosθ	0
0		0		0		1
*/
float	*mat4_rotate_x(float angle, float *result)
{
	size_t	i;

	i = 0;
	while (i < MAT4_SIZE)
	{
		if (i == 0 || i == 15)
			result[i] = 1;
		else if (i == 5 || i == 10)
			result[i] = cosf(angle);
		else if (i == 6)
			result[i] = sinf(angle);
		else if (i == 9)
			result[i] = -sinf(angle);
		else
			result[i] = 0;
		i++;
	}
	return (result);
}

/*
4x4 rotating matrix (y-axis)
cosθ	0		sinθ	0
0		1		0		0
-sinθ	0		cosθ	0
0		0		0		1
*/
float	*mat4_rotate_y(float angle, float *result)
{
	size_t	i;

	i = 0;
	while (i < MAT4_SIZE)
	{
		if (i == 5 || i == 15)
			result[i] = 1;
		else if (i == 0 || i == 10)
			result[i] = cosf(angle);
		else if (i == 2)
			result[i] = -sinf(angle);
		else if (i == 8)
			result[i] = sinf(angle);
		else
			result[i] = 0;
		i++;
	}
	return (result);
}

/*
4x4 rotating matrix (z-axis)
cosθ	-sinθ	0		0
sinθ	cosθ	0		0
0		0		1		0
0		0		0		1
*/
float	*mat4_rotate_z(float angle, float *result)
{
	size_t	i;

	i = 0;
	while (i < MAT4_SIZE)
	{
		if (i == 10 || i == 15)
			result[i] = 1;
		else if (i == 0 || i == 5)
			result[i] = cosf(angle);
		else if (i == 1)
			result[i] = sinf(angle);
		else if (i == 4)
			result[i] = -sinf(angle);
		else
			result[i] = 0;
		i++;
	}
	return (result);
}
