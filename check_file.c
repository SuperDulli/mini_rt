/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:24:17 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/24 11:17:56 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	checkfile(char *path)
{
	int	fd;
	int	suffix;

	suffix = ft_strlen(path);
	if (suffix > 3)
	{
		if (ft_strncmp(path + suffix - 3, ".rt", 3))
		{
			ft_putendl_fd("Invalid file extension", 1);
			return (-1);
		}
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(path);
		return (-1);
	}
	return (readfile(fd));
}

int	readfile(int fd)
{
	char	*line;
	char	*temp;
	int		err;

	line = get_next_line(fd);
	if (!line)
	{
		ft_putendl_fd("File empty!", 1);
		return (-1);
	}
	err = 0;
	while (line)
	{
		if (*line != '\n' && err != -1)
		{
			replace_tabs(line);
			temp = ft_strtrim(line, " ");
			err = checkline(temp);
			free(temp);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (err == -1)
	{
		ft_putendl_fd("Invalid file!", 1);
		return (-1);
	}
	return (0);
}

int	checkline(char *line)
{
	if (!*line)
		return (0);
	else if (!ft_strncmp(line, "A ", 2))
		return (check_amlight(line));
	else if (!ft_strncmp(line, "C ", 2))
		return (check_camera(line));
	else if (!ft_strncmp(line, "L ", 2))
		return (check_light(line));
	else if (!ft_strncmp(line, "sp ", 3))
		return (check_sphere(line));
	else if (!ft_strncmp(line, "pl ", 3))
		return (check_plane(line));
	else if (!ft_strncmp(line, "cy ", 3))
		return (check_cylinder(line));
	else
		return (-1);
}

int	check_cylinder(char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 6)
	{
		if (!check_vector(arg[1]) && !check_vector(arg[2]) && \
			!check_float(arg[3]) && !check_float(arg[4]) && \
			!check_color(arg[5]))
		{
			arr_free(arg);
			return (0);
		}
	}
	arr_free(arg);
	return (-1);
}

// t_obj	**obj;
// obj = malloc(sizeof(t_obj *) * 5);
// obj[0] = malloc(sizeof(t_obj));
// obj[0]->specifics = malloc(sizeof(t_sphere));
// obj[1]->speficis = malloc(sizeof(t_cylinder));

// // t_sphere  *temp;
// // temp = (t_sphere *) obj->specifics;
// // temp->diameter = 2.5f;
// ((t_sphere *) obj[0]->specifics)->diamater = 2.5f;
// ((t_cylinder *) obj[1]->specifics)->hight = 10.8f;
