/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:55:12 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/08 16:25:35 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int check_amlight(char *line)
{
	char	**arr;
	char	*temp;
	int		len;
	int		i;

	arr = ft_split(line, ' ');
	len = 0;
	while (arr[len])
		len++;
	if (len > 3)
		return (-1);
	ft_putendl_fd("Valid arguments for amlight!", 1);
	i = 1;
	while (i < len)
	{
		temp = ft_strtrim(arr[i], "\t \n");
		free(arr[i]);
		arr[i] = temp;
		i++;
	}
	ft_putendl_fd(arr[0], 1);
	ft_putendl_fd(arr[1], 1);
	ft_putendl_fd(arr[2], 1);

	free(arr[0]);
	free(arr[1]);
	free(arr[2]);
	free(arr[3]);
	free(arr);
	// 	while
	// }

	// line++;
	// while (*line && (*line == ' ' || *line == '\t'))
	// 	line++;
	// if (ft_isdigit(*line) && *(line +1) == '.' && ft_isdigit(*(line + 2)))
	// 	line += 3;
	// else
	// 	return (-1);
	// printf("%s\n", line);
	// printf("%d\n", len);
	// printf("%d\n", len);
	return(0);
}