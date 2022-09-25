/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:24:17 by pcordeir          #+#    #+#             */
/*   Updated: 2022/09/25 16:32:29 by chelmerd         ###   ########.fr       */
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
			ft_error(1, "Invalid file extension");
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
	int		err;

	line = get_next_line(fd);
	if (!line)
	{
		ft_error(2, "File empty!");
		return (-1);
	}
	err = 0;
	readfile_helper(line, fd, &err);
	close(fd);
	if (!err)
		return (0);
	ft_error(3, "Invalid file!");
	return (-1);
}

int	checkline(char *line, char *duplicate)
{
	if (!*line)
		return (0);
	if (!ft_strncmp(line, "A ", 2) && ((*duplicate & 1) == 0))
		return (check_amlight(line, duplicate));
	if (!ft_strncmp(line, "C ", 2) && (((*duplicate >> 1) & 1) == 0))
		return (check_camera(line, duplicate));
	if (!ft_strncmp(line, "L ", 2) && (((*duplicate >> 2) & 1) == 0))
		return (check_light(line, duplicate));
	if (!ft_strncmp(line, "sp ", 3))
		return (check_sphere(line));
	if (!ft_strncmp(line, "pl ", 3))
		return (check_plane(line));
	if (!ft_strncmp(line, "cy ", 3))
		return (check_cylinder(line));
	return (-1);
}

int	check_cylinder(char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (arr_size(arg) == 6)
	{
		if (!check_vector(arg[1]) && !check_vector_range(arg[2], -1, 1) && \
			(!check_string_range(arg[3], 0, 0) && \
			!check_string_range(arg[4], 0, 0)) && !check_color(arg[5], 0))
		{
			arr_free(arg);
			return (0);
		}
	}
	arr_free(arg);
	return (-1);
}

void	readfile_helper(char *line, int fd, int *err)
{
	char	*temp;
	char	duplicate;

	duplicate = 0;
	while (line)
	{
		if (*line != '\n' && *err == 0)
		{
			replace_tabs(line);
			temp = ft_strtrim(line, " ");
			*err = checkline(temp, &duplicate);
			free(temp);
		}
		free(line);
		line = get_next_line(fd);
	}
}
