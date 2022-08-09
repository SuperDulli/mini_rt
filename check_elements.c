/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:55:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/09 12:00:10 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int check_amlight(char *line)
{
	char	**arr;

	ft_putendl_fd(line, 1); //testing
	arr = ft_split(line, ' ');
	if (arr_size(arr) > 3)
		return (-1);
	ft_putendl_fd("Valid arguments for amlight!", 1); //testing
	trim_info(arr);
	ft_putendl_fd(arr[0], 1);
	ft_putendl_fd(arr[1], 1);
	ft_putendl_fd(arr[2], 1);
	arr_free(arr);

	return(0);
}