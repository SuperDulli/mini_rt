/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:02:38 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 20:06:49 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

unsigned int	get_color(unsigned alpha, unsigned r, unsigned g, unsigned b)
{
	unsigned int	color;

	color = 0;
	color += (alpha << 24);
	color += (r << 16);
	color += (g << 8);
	color += b;
	return (color);
}

float	*color_vec(float color[VEC3_SIZE], float *result)
{
	const float	divisor = 255.f;

	if (0 > color[0] || color[0] > 255 || 0 > color[1] || color[1] > 255 || \
		0 > color[2] || color[2] > 255)
	{
		ft_error(1, "colors not in 0 to 255 range.");
	}
	result = vec3(color[0] / divisor, color[1] / divisor, color[2] / divisor, \
				result);
	return (result);
}

int	convert_to_argb(float rgb[VEC3_SIZE])
{
	int	color;
	int	red;
	int	green;
	int	blue;

	vec3_clamp(rgb, 0.0f, 1.0f, rgb);
	if (0.f > rgb[0] || rgb[0] > 1.f || 0.f > rgb[1] || rgb[1] > 1.f || \
		0.f > rgb[2] || rgb[2] > 1.f)
	{
		printf("rgb(%f,%f,%f)\n", rgb[0], rgb[1], rgb[2]);
		ft_error(1, "colors not in 0.0 to 1.0 range.");
	}
	red = rgb[0] * 255;
	green = rgb[1] * 255;
	blue = rgb[2] * 255;
	color = (0 << 24) | (red << 16) | (green << 8) | blue;
	return (color);
}
