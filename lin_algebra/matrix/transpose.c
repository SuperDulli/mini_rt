/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:11:05 by chelmerd          #+#    #+#             */
/*   Updated: 2022/07/16 15:29:15 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

float	*mat_transpose(float *m, size_t dim, float *result)
{
	size_t	i;
	size_t	j;
	size_t	idx;
	size_t	idx_t;
	float	tmp;

	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < i)
		{
			idx = j * dim + i;
			idx_t = i * dim + j;
			tmp = m[idx];
			result[idx] = m[idx_t];
			result[idx_t] = tmp;
			j++;
		}
		idx = j * dim + i;
		result[idx] = m[idx];
		i++;
	}
	return (result);
}
