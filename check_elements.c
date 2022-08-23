/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:55:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/23 18:18:49 by pcordeir         ###   ########.fr       */
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
	int		res;

	arr = ft_split(line, ' ');
	if (arr_size(arr) == 4)
	{
		if (!check_vector(arr[1]) && !check_vector(arr[2])) // && !check_int(arr[3]))
		{
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
	arr_free(arr);
	return (-1);
}

int	check_light(char *line)
{
	char	**arg;
	float	res;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 4)
	{
		if (!check_vector(arg[1]) && !check_color(arg[3]))
		{
			if (!check_float(arg[2]))
			{
				res = ft_atof(arg[2]);
				if (res >= 0 && res <= 1)
				{
					arr_free(arg);
					return (0);
				}
			}
		}
	}
	arr_free(arg);
	return (-1);
}

// int	check_sphere(char *line)
// {

// }
