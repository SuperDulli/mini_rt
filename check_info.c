/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:28:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/12 14:16:43 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_color(char *color)
{
	char	**arr;
	int		i;
	int		res;

	arr = ft_split(color, ',');
	if (arr_size(arr) == 3)
	{
		i = 0;
		while (arr[i] && !check_int(arr[i]))
		{
			res = ft_atoi(arr[i]);
			if (res >= 0 && res <= 255)
				i++;
			else
				break ;
		}
	}
	arr_free(arr);
	if (i == 3)
		return (0);
	else
		return (-1);
}

int	check_int(char *info)
{
	int		sign;
	int		res;
	long	temp;

	sign = 1;
	res = 1;
	temp = 0;
	if (*info == '+' || *info == '-')
	{
		if (*info == '-')
			sign = -1;
		info++;
	}
	while (*info && ft_isdigit(*info))
	{
		temp = temp * 10 + (*info - '0');
		info++;
	}
	if (!*info)
	{
		temp *= sign;
		res = (int)temp;
	}
	return ((res == temp) - 1);
}

int	check_vector(char *vector)
{
	char	**arr;

	arr = ft_split(vector, ',');
	if (arr_size(arr) == 3)
	{
		if (!check_float(arr[0]) && !check_float(arr[0]) && !check_float(arr[0]))
			return (0);
	}
	return (-1);
}