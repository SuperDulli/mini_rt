/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:40:15 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/23 15:27:35 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		max_float = 2000;
unsigned int	max_precision = 4;	//where to define this?

#include "mini_rt.h"

int	arr_size(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	arr_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	replace_tabs(char *line)
{
	while (*line)
	{
		if (*line == '\t' || *line == '\n')
			*line = ' ';
		line++;
	}
}

int	check_float(char *info)
{
	char	**arr;
	int		prefix;

	arr = ft_split(info, '.');
	if (arr_size(arr) == 2)
	{
		if (ft_isdigit(*arr[1]))
		{
			if (!check_int(arr[0]) && !check_int(arr[1]))
			{
				prefix = ft_atoi(arr[0]);
				if (prefix <= max_float && prefix >= max_float * -1 \
					&& ft_strlen(arr[1]) <= max_precision)
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

float	ft_atof(const char *str)
{
	char	**arr;
	float	res;

	arr = ft_split(str, '.');
	res = ft_atoi(arr[0]);
	if (*arr[0] == '-')
		res -= (float)(ft_atoi(arr[1])) / pow(10, ft_strlen(arr[1]));
	else
		res += (float)(ft_atoi(arr[1])) / pow(10, ft_strlen(arr[1])); //we are allowed to use pow() from math.h right?
	arr_free(arr);
	return (res);
}
