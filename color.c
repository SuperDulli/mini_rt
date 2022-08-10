/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:02:38 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/10 12:11:29 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	get_red(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_blue(int color)
{
	return (color & 0xFF);
}

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


// alpha can be ignored - not used in the project
// [0, 255] -> [0.f, 1.f]
float	*color_vec(int red, int green, int blue, float *result)
{
	const float divisor = 255.f; // 255 -> exact 1.0 at 255; 254 -> exact -> 0.5 at 127

	if (0 > red || red > 255 || 0 > green || green > 255 || 0 > blue || blue > 255)
	{
		ft_error(1, "colors not in 0 to 255 range.");
	}

	result = vec3(
		red / divisor,
		green / divisor,
		blue / divisor,
		result);
	return (result);
}

// 0xAARRGGBB -> vec3(r, g, b) where 0.f <= r,g,b <= 1.f
float	*color_vec_from_int(int argb, float *result)
{
	int	red;
	int	green;
	int	blue;

	// alpha = arbg >> 24;
	red = (argb >> 16) & 0xFF;
	green = (argb >> 8) & 0xFF;
	blue = argb & 0xFF;

	return (color_vec(red, green, blue, result));
}

// [0.f, 1.f] -> [0, 255]
int	convert_to_argb(float rgb[VEC3_SIZE])
{
	int	color;
	int	red;
	int	green;
	int	blue;

	vec3_clamp(rgb, 0.0f, 1.0f, rgb);

	if (0.f > rgb[0] || rgb[0] > 1.f || 0.f > rgb[1] || rgb[1] > 1.f || 0.f > rgb[2] || rgb[2] > 1.f)
	{
		// should be dead code because of clamp()
		printf("rgb(%f,%f,%f)\n", rgb[0], rgb[1], rgb[2]);
		ft_error(1, "colors not in 0.0 to 1.0 range.");
	}

	red = rgb[0] * 255;
	green = rgb[1] * 255;
	blue = rgb[2] * 255;

	// printf("red=%X, green=%X, blue=%X\n", red, green, blue);
	color = (0 << 24) | (red << 16) | (green << 8) | blue;
	return (color);
}

// int main()
// {
// 	float	color[VEC3_SIZE];
// 	int		color_code;

// 	color_code = BLUE;
// 	color_vec(0, 0, 255, color);
// 	convert_to_argb(color);
// 	printf("color=(%f,%f,%f), color_code=%X, convert_to_argb=%X\n", color[0], color[1], color[2], color_code, convert_to_argb(color));
// 	color_vec_from_int(color_code, color);
// 	printf("color_vec_from_int=(%f,%f,%f)\n", color[0], color[1], color[2]);
// 	printf("\n");

// 	color_code = (((GREEN >> 8) / 2) << 8) | (BLUE / 2);
// 	color_vec(0, 127, 127, color);
// 	convert_to_argb(color);
// 	printf("color=(%f,%f,%f), color_code=%X, convert_to_argb=%X\n", color[0], color[1], color[2], color_code, convert_to_argb(color));
// 	color_vec_from_int(color_code, color);
// 	printf("color_vec_from_int=(%f,%f,%f)\n", color[0], color[1], color[2]);
// 	printf("\n");

// 	color_code = (((GREEN >> 8) / 2) << 8) | (BLUE / 2);
// 	color_vec(0, 128, 128, color);
// 	convert_to_argb(color);
// 	printf("color=(%f,%f,%f), color_code=%X, convert_to_argb=%X\n", color[0], color[1], color[2], color_code, convert_to_argb(color));
// 	color_vec_from_int(color_code, color);
// 	printf("color_vec_from_int=(%f,%f,%f)\n", color[0], color[1], color[2]);
// 	printf("\n");

// 	vec3(0, 0.5f, 0.f, color);
// 	color_code = convert_to_argb(color);
// 	printf("color=(%f,%f,%f), color_code=%X, convert_to_argb=%X\n", color[0], color[1], color[2], color_code, convert_to_argb(color));
// 	color_vec_from_int(color_code, color);
// 	printf("color_vec_from_int=(%f,%f,%f)\n", color[0], color[1], color[2]);
// 	printf("\n");
// 	return 0;
// }
