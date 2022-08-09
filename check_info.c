/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:28:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/09 16:35:44 by chelmerd         ###   ########.fr       */
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
	// return (0);
}
