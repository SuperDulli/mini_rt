/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:24:17 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/04 13:40:54 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	checkfile(char *path)
{
	int	fd;

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
		printf("File empty!\n");
		return (-1);
	}
	err = 0;
	while (line)
	{
		if (*line != '\n' && err != -1)
		{
			printf("Line: %s", line);
			err = checkline(line);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return(0);
}

int	checkline(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))		// recognize tabs? 
		line++;
	if (!*line || *line == '\n')
		return (0);
	else if (*line == 65)
		return (printf("Create amlight!\n"));
		// return (create_amlight(line));
	else if (*line == 67)
		return (printf("Create camera!\n"));
		// return (create_camera(line));
	else if (*line == 76)
		return (printf("Create light!\n"));
		// return (create_light(line));
	else if (*line == 115 && *(line + 1) == 112)
		return (printf("Create sphere!\n"));
		// return (create_sphere(line));
	else if (*line == 112 && *(line + 1) == 108)
		return (printf("Create plane!\n"));
		// return (create_plane(line));
	else if (*line == 99 && *(line + 1) == 121)
		return (printf("Create cylinder!\n"));
		// return (create_cylinder(line));
	else
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
