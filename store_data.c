/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:59:30 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/31 17:04:47 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	store_data(char *path, t_scene	*scene)
{
	int		fd;
	char	*line;
	int		err;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	err = 0;
	get_data(line, fd, &err, scene);
	close(fd);
	if (!err)
		return (0);
	ft_putendl_fd("Error while reading file!", 1);
	return (-1);
}

void	get_data(char *line, int fd, int *err, t_scene *scene)
{
	char	*temp;

	while (line)
	{
		if (*line != '\n' && *err == 0)
		{
			replace_tabs(line);
			temp = ft_strtrim(line, " ");
			*err = save_data(temp, scene);
			free(temp);
		}
		free(line);
		line = get_next_line(fd);
	}
}

int	save_data(char *line, t_scene *scene)
{
	if (!*line)
		return (0);
	if (!ft_strncmp(line, "A ", 2))
		return (save_amlight(line, scene));
	// if (!ft_strncmp(line, "C ", 2))
	// 	return (save_camera(line, scene));
	// if (!ft_strncmp(line, "L ", 2))
	// 	return (save_light(line, scene));
	if (!ft_strncmp(line, "sp ", 3))
		return (save_sphere(line, scene));
	// if (!ft_strncmp(line, "pl ", 3))
	// 	return (save_plane(line, scene));
	// if (!ft_strncmp(line, "cy ", 3))
	// 	return (save_cylinder(line, scene));
	return (-1);
}

int	str_to_vec(char *info, float *vec)
{
	char	**pos;

	pos = ft_split(info, ',');
	if (!pos)
		return (-1);
	vec3(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]), vec);
	arr_free(pos);
	return(0);
}