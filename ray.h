/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:00:09 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/05 15:01:32 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"

struct s_ray
{
	float	origin[VEC3_SIZE];
	float	direction[VEC3_SIZE];
};

float	*ray_at(struct s_ray *ray, float t, float *point);
void	ray_cast(float *origin, float *point, struct s_ray *ray);

#endif
