/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:40:15 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/31 11:59:57 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	arr_size(char **arr)
{
	int	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}

void	arr_free(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
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
	float	res;
	int		sign;

	sign = 1;
	res = ft_atoi(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		str++;
		if (sign == 1)
			res += (float)(ft_atoi(str)) / pow(10, ft_strlen(str));
		else
			res -= (float)(ft_atoi(str)) / pow(10, ft_strlen(str));
	}
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
