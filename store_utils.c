/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:37:58 by pcordeir          #+#    #+#             */
/*   Updated: 2022/09/03 12:43:19 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	file not necessary atm!

#include "mini_rt.h"

int	str_to_vec(char *info, float *vec)
{
	char	**pos;

	pos = ft_split(info, ',');
	if (!pos)
		return (-1);
	vec3(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]), vec);
	arr_free(pos);
	return(0);
}

// int	str_to_color(char *info)
// {
// 	char	**rgb;
// 	int		res;

// 	res = -1;
// 	rgb = ft_split(info);
// 	if (rgb)
// 	{
// 		res = get_color(0, rgb[0], rgb[1], rgb[2]);
// 		arr_free(rgb);
// 	}
// 	return (res);
// }