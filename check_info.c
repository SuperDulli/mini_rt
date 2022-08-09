/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:28:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/09 15:13:15 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_color(char *color)
{
	char	**arr;
	int		i;

	arr = ft_split(color, ',');
	if (arr_size(arr) == 3)
	{
		i = 0;
		while (arr[i] && !check_int(arr[i]))
		{
			if (ft_atoi(arr[i]) >= 0 && ft_atoi(arr[i]) <= 255)
				i++;
			else
				break ;
		}
		if (i == 3)
		{
			arr_free(arr);
			return (0);
		}
	}
	arr_free(arr);
	return (-1);
}

int	check_int(char *info)
{
	int	i;

	i = 1;
	while (info[i])
	{
		if (ft_isdigit(info[i]))
			i++;
		else
			break ;
	}
	if (info[i] == '\0')
		return (0);
	else
		return (-1);
	return (0);
}