/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:28:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/23 18:19:22 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		max_float = 2000;
unsigned int	max_precision = 4;	//where to define this?

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

int	check_vector(char *argument)
{
	char	**vector;
	int 	i;

	vector = ft_split(argument, ',');
	if (arr_size(vector) == 3)
	{
		i = 0;
		while(vector[i])
		{
			if (!check_float(vector[i]) || !check_int(vector[i]))
				i++;
			else
				break ;
		}
		if (i == 3)
		{
			arr_free(vector);
			return (0);
		}
	}
	arr_free(vector);
	return (-1);
}