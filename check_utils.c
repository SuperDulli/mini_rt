/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:40:15 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/24 16:48:14 by pcordeir         ###   ########.fr       */
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
	if (*arr[0] == '-')
		res -= (float)(ft_atoi(arr[1])) / pow(10, ft_strlen(arr[1]));
	else
		res += (float)(ft_atoi(arr[1])) / pow(10, ft_strlen(arr[1]));
	arr_free(arr);
	return (res);
}

int	check_float_range(float nbr, int min, int max)
{
	return (min <= nbr && nbr <= max);
}
