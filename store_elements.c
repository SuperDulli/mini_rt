/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcordeir <pcordeir@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:08:56 by pcordeir          #+#    #+#             */
/*   Updated: 2022/08/31 16:59:26 by pcordeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	save_amlight(char *line, t_scene *scene)
{
	char	**arg;
	char	**color;

	arg = ft_split(line, ' ');
	if (arg)
		color = ft_split(arg[2], ',');
	if (color)
	{
		scene->ambient_light = new_ambient_light(ft_atof(arg[1]), \
		get_color(0, ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2])));
		arr_free(color);
		arr_free(arg);
		if (scene->ambient_light)
			return (0);
	}
	return (-1);
}

int	save_sphere(char *line, t_scene *scene)
{
	char	**arg;
	char	**color;
	t_obj	*sphere;
	float	vec[VEC3_SIZE];

	arg = ft_split(line, ' ');
	if (arg)
		color = ft_split(arg[3], ',');
	if (color && !str_to_vec(arg[1], vec))
	{
		sphere = new_sphere(vec, get_color(0, ft_atoi(color[0]), \
			ft_atoi(color[1]), ft_atoi(color[2])), ft_atof(arg[2]));
		arr_free(arg);
		arr_free(color);
		if (sphere && add_obj_to_scene(scene, sphere))
			return (0);
		destroy_object(sphere);
	}
	return (-1);
}
