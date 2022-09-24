/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:55:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/09/03 12:42:03 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_amlight(char *line, char *duplicate)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 3)
	{
		if (!check_string_range(arg[1], 0, 1) && !check_color(arg[2], 0))
		{
			arr_free(arg);
			*duplicate |= 1;
			return (0);
		}
	}
	arr_free(arg);
	return (-1);
}

int	check_camera(char *line, char *duplicate)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 4)
	{
		if (!check_vector(arg[1]) && !check_vector_range(arg[2], -1, 1) && \
			!check_string_range(arg[3], MIN_FOV, MAX_FOV))
		{
			arr_free(arg);
			*duplicate |= 1 << 1;
			return (0);
		}
	}
	arr_free(arg);
	return (-1);
}

int	check_light(char *line, char *duplicate)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 4)
	{
		if (!check_vector(arg[1]) && !check_string_range(arg[2], 0, 1) && \
			!check_color(arg[3], 1))
		{
			arr_free(arg);
			*duplicate |= 1 << 2;
			return (0);
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
		if (!check_vector(arg[1]) && !check_color(arg[3], 0) && \
			(!check_string_range(arg[2], 0, 0)))
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
		if (!check_vector(arg[1]) && !check_vector_range(arg[2], -1, 1) && \
			!check_color(arg[3], 0))
		{
			arr_free(arg);
			return (0);
		}
	}
	arr_free(arg);
	return (-1);
}
