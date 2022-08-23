/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:55:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/23 15:55:15 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_amlight(char *line)
{
	char	**arr;
	float	res;

	arr = ft_split(line, ' ');
	if (arr_size(arr) == 3)
	{
		if (!check_float(arr[1]) && !check_color(arr[2]))
		{
			res = ft_atof(arr[1]);
			if (0 <= res && res <= 1)
			{
				arr_free(arr);
				return (0);
			}
		}
	}
	arr_free(arr);
	return (-1);
}

int	check_camera(char *line)
{
	//		vectors can be floats or ints!!!!!
	char	**arr;
	char	**vector;
	int		res;

	arr = ft_split(line, ' ');
	if (arr_size(arr) == 4)
	{
		vector = ft_split(arr[1], ',');
		if (!check_vector(vector))
		{
			arr_free(vector);
			vector = ft_split(arr[2], ',');
			// printf("Second Vector Size: %d\n", arr_size(vector)); //testing
			if (!check_vector(vector))
			{
				arr_free(vector);
				if (!check_int(arr[3]))		//FOV int or float?
				{
					res = ft_atoi(arr[3]);
					if (0 <= res && res <= 180)
					{
						arr_free(arr);
						return (0);
					}
				}
			}
		}
		arr_free(vector);
	}
	arr_free(arr);
	return (-1);
}
