/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:59:30 by pcordeir          #+#    #+#             */
/*   Updated: 2022/09/01 13:40:50 by pcordeir         ###   ########.fr       */
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
	if (!ft_strncmp(line, "C ", 2))
		return (save_camera(line, scene));
	if (!ft_strncmp(line, "L ", 2))
		return (save_light(line, scene));
	if (!ft_strncmp(line, "sp ", 3))
		return (save_sphere(line, scene));
	if (!ft_strncmp(line, "pl ", 3))
		return (save_plane(line, scene));
	if (!ft_strncmp(line, "cy ", 3))
		return (save_cylinder(line, scene));
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
	return (0);
}

int	save_cylinder(char *line, t_scene *scene)
{
	t_obj	*cylinder;
	char	**arg;
	char	**color;
	float	pos[VEC3_SIZE];
	float	vec[VEC3_SIZE];

	arg = ft_split(line, ' ');
	if (arg)
		color = ft_split(arg[5], ',');
	if (color && !str_to_vec(arg[1], pos) && !str_to_vec(arg[2], vec))
	{
		cylinder = new_cylinder(pos, get_color(0, ft_atoi(color[0]), \
					ft_atoi(color[1]), ft_atoi(color[2])), vec, \
					ft_atof(arg[3]), ft_atof(arg[4]));
		arr_free(color);
		arr_free(arg);
		if (add_obj_to_scene(scene, cylinder))
			return (0);
		destroy_object(cylinder);
	}
	return (-1);
}
