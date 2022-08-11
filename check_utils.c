/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:40:15 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/11 15:31:01 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		max_float = 2000;
unsigned int	max_precision = 3;

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
					return (0);
			}
		}
	}
	return (-1);
}

float	ft_atof(const char *str)
{
	char	**arr;
	float	res;

	arr = ft_split(str, '.');
	ft_putendl_fd(arr[0], 1);
	res = ft_atoi(arr[0]) + (float)(ft_atoi(arr[1])) / (10 * ft_strlen(arr[1])); //doesn't handle negative floats!
	arr_free(arr);
	return (res);
}
