/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:55:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/12 13:38:09 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_amlight(char *line)
{
	char	**arr;
	float	res;

	arr = ft_split(line, ' ');
	// ft_putendl_fd(arr[0], 1);
	// ft_putendl_fd(arr[1], 1);
	// ft_putendl_fd(arr[2], 1);
	if (arr_size(arr) == 3)
	{
		if (/*!check_float(arr[1]) && */!check_color(arr[2])) //testing
		{
			res = ft_atof(arr[1]);
			if (0 <= res && res <= 1)
			{
				arr_free(arr);
				return (0);
			}
		}
	}
	arr_free(arr);
	return (-1);
}
