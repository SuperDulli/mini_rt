/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:08:56 by pcordeir          #+#    #+#             */
/*   Updated: 2022/09/04 16:53:02 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	save_amlight(char *line, t_scene *scene)
{
	char	**arg;
	float	color[VEC3_SIZE];

	arg = ft_split(line, ' ');
	if (arg && !str_to_vec(arg[2], color))
	{
		scene->ambient_light = new_ambient_light(ft_atof(arg[1]), \
								color_vec(color, color));
		arr_free(arg);
		if (scene->ambient_light)
			return (0);
	}
	return (-1);
}

int	save_camera(char *line, t_scene *scene)
{
	char	**arg;
	float	pos[VEC3_SIZE];
	float	vec[VEC3_SIZE];

	arg = ft_split(line, ' ');
	if (arg && !str_to_vec(arg[1], pos) && !str_to_vec(arg[2], vec))
	{
		scene->camera = new_camera(pos, vec, ft_atof(arg[3]));
		arr_free(arg);
		if (scene->camera)
			return (0);
	}
	return (-1);
}

int	save_light(char *line, t_scene *scene)
{
	char	**arg;
	float	pos[VEC3_SIZE];
	float	color[VEC3_SIZE];

	arg = ft_split(line, ' ');
	if (arg && !str_to_vec(arg[1], pos) && !str_to_vec(arg[3], color))
	{
		scene->light = new_light(pos, color_vec(color, color), ft_atof(arg[2]));
		arr_free(arg);
		if (scene->light)
			return (0);
	}
	return (-1);
}

int	save_sphere(char *line, t_scene *scene)
{
	t_obj	*sphere;
	char	**arg;
	float	color[VEC3_SIZE];
	float	pos[VEC3_SIZE];

	arg = ft_split(line, ' ');
	if (arg && !str_to_vec(arg[1], pos) && !str_to_vec(arg[3], color))
	{
		sphere = new_sphere(pos, color_vec(color, color), ft_atof(arg[2]));
		arr_free(arg);
		if (add_obj_to_scene(scene, sphere))
			return (0);
		destroy_object(sphere);
	}
	return (-1);
}

int	save_plane(char *line, t_scene *scene)
{
	t_obj	*plane;
	char	**arg;
	float	color[VEC3_SIZE];
	float	pos[VEC3_SIZE];
	float	vec[VEC3_SIZE];

	arg = ft_split(line, ' ');
	if (arg && !str_to_vec(arg[1], pos) && !str_to_vec(arg[2], vec) && \
		!str_to_vec(arg[3], color))
	{
		plane = new_plane(pos, color_vec(color, color), vec);
		arr_free(arg);
		if (add_obj_to_scene(scene, plane))
			return (0);
		destroy_object(plane);
	}
	return (-1);
}
