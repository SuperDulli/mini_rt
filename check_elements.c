/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:55:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/24 16:48:55 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_amlight(char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 3)
	{
		if (!check_float(arg[1]) && !check_color(arg[2]))
		{
			if (check_float_range(ft_atof(arg[1]), 0, 1))
			{
				arr_free(arg);
				return (0);
			}
		}
	}
	arr_free(arg);
	return (-1);
}

int	check_camera(char *line)
{
	// FOV allowed 120.0?
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 4)
	{
		if (!check_vector(arg[1]) && !check_vector(arg[2]) && \
			!check_int(arg[3]))
		{
			if (check_float_range(ft_atoi(arg[3]), 0, 180))
			{
				arr_free(arg);
				return (0);
			}
		}
	}
	arr_free(arg);
	return (-1);
}

int	check_light(char *line)
{
	// brightness 1 allowed?
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 4)
	{
		if (!check_vector(arg[1]) && !check_float(arg[2]) && \
			!check_color(arg[3]))
		{
			if (check_float_range(ft_atof(arg[2]), 0, 1))
			{
				arr_free(arg);
				return (0);
			}
		}
	}
	arr_free(arg);
	return (-1);
}

int	check_sphere(char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 4)
	{
		if (!check_vector(arg[1]) && !check_color(arg[3]) && \
			(!check_float(arg[2]) || !check_int(arg[2])))
		{
			arr_free(arg);
			return (0);
		}
	}
	arr_free(arg);
	return (-1);
}

int	check_plane(char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 4)
	{
		if (!check_vector(arg[1]) && !check_vector(arg[2]) && \
			!check_color(arg[3]))
		{
			arr_free(arg);
			return (0);
		}
	}
	arr_free(arg);
	return (-1);
}
