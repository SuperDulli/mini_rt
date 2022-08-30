/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:40:15 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/30 13:24:11 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

float	ft_atof(const char *str)
{
	char	**arr;
	float	res;

	arr = ft_split(str, '.');
	res = ft_atoi(arr[0]);
	if (*arr[0] == '-' && arr[1])
		res -= (float)(ft_atoi(arr[1])) / pow(10, ft_strlen(arr[1]));
	else if (arr[1])
		res += (float)(ft_atoi(arr[1])) / pow(10, ft_strlen(arr[1]));
	arr_free(arr);
	return (res);
}

int	check_string_range(char *str, int min, int max)
{
	float	res;
	int		temp;

	temp = check_float(str);
	if (!temp || !check_int(str))
	{
		if (!temp)
			res = ft_atof(str);
		else
			res = ft_atoi(str);
		if (min <= res && res <= max)
			return (0);
	}
	return (-1);
}
