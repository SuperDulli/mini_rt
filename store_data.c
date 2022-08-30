/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:59:30 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/30 15:38:21 by pcordeir         ###   ########.fr       */
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
			free(temp)
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
	// 	return (save_camera(line));
	// if (!ft_strncmp(line, "L ", 2))
	// 	return (save_light(line));
	if (!ft_strncmp(line, "sp ", 3))
		return (save_sphere(line, scene));
	// if (!ft_strncmp(line, "pl ", 3))
	// 	return (save_plane(line));
	// if (!ft_strncmp(line, "cy ", 3))
	// 	return (save_cylinder(line));
	return (-1);
}

int	save_amlight(char *line, t_scene *scene)
{
	char	**arg;
	char	**color;

	arg = ft_split(line, ' ');
	color = ft_split(arr[2], ',');
	scene->ambient_light = new_ambient_light(ft_atof(arg[1]), \
		get_color(0, ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2])));
	arr_free(color);
	arr_free(arg);
	if (!scene->ambient_light)
		return (-1);
	return (0);
}

int	save_sphere(char *line, t_scene *scene)
{
	char	**arg;
	char	**color;
	t_obj	*sphere;
	float	vec[VEC3_SIZE];

	arg = ft_split(line, ' ');
	if (arg)
	{
		if (!str_to_vec(arg[1], vec))
		{
			color = ft_split(arg[3], ',');
			if (color)
			{
				sphere = new_sphere(vec, get_color(0, ft_atoi(color[0]), \
					ft_atoi(color[1]), ft_atoi(color[2])), ft_atof(arg[2]));
				if (sphere)
				{
					if (!add_obj_to_scene(scene, sphere));
						destroy_object(sphere);
				}
				arr_free(color);
			}
		}
		arr_free(arg);
	}
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