/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:40:15 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/09 17:00:29 by chelmerd         ###   ########.fr       */
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

void	trim_info(char **arr)
{
	int 	i;
	char	*temp;

	i = 1;
	while (arr[i])
	{
		temp = ft_strtrim(arr[i], "\t "); // do we need to look for spaces anymore?
		free(arr[i]);
		arr[i] = temp;
		i++;
	}
}

int	check_float(char *info)
{
	float	res;

	if (ft_strlen(info) != 3)
		return (-1);
	if (ft_isdigit(*info) && *(info + 1) == '.' && ft_isdigit(*(info + 2)))
		res = ft_atof(info);
	if (res >= 0 && res <= 1)
		return (0);
	else
		return (-1);
}

float	ft_atof(const char *str)
{
	char	**arr;
	float	res;

	arr = ft_split(str, '.');
	res = ft_atoi(arr[0]) + (float)(ft_atoi(arr[1])) / (10 * ft_strlen(arr[1]));
	arr_free(arr);
	return (res);
}
