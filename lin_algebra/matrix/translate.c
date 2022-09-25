/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:35:33 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/20 12:39:02 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

/*
4x4 translating matrix
1 0 0 x
0 1 0 y
0 0 1 z
0 0 0 1
*/
float	*mat4_translate(float x, float y, float z, float *result)
{
	size_t	i;

	i = 0;
	while (i < MAT4_SIZE)
	{
		if (i % 5 == 0)
			result[i] = 1;
		else if (i == 12)
			result[i] = x;
		else if (i == 13)
			result[i] = y;
		else if (i == 14)
			result[i] = z;
		else
			result[i] = 0;
		i++;
	}
	return (result);
}
