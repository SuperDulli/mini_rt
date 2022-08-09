/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:55:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/09 16:18:01 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int check_amlight(char *line)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (arr_size(arr) > 3) //why > and not ==
		return (-1);
	trim_info(arr);
	if (check_float(arr[1]) == -1 || check_color(arr[2]) == -1)
	{
		arr_free(arr);
		return (-1);
	}
	arr_free(arr);
	return(0);
}
