/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:15:00 by chelmerd          #+#    #+#             */
/*   Updated: 2022/09/25 16:22:57 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	fill_hit_record(float *pos, float *normal, float *color,
						t_hit_record *hit)
{
	vec3_copy(pos, hit->pos);
	vec3_copy(normal, hit->normal);
	vec3_copy(color, hit->color);
}

t_hit_record	*new_hit_record(float *pos, float *normal, float *color)
{
	t_hit_record	*hit_record;

	hit_record = new(sizeof(t_hit_record));
	if (!hit_record)
	{
		return (NULL);
	}
	fill_hit_record(pos, normal, color, hit_record);
	return (hit_record);
}

bool	add_hit_record(t_list **records, t_hit_record *hit)
{
	t_list	*elem;

	if (!hit)
	{
		ft_error(1, "add_hit_record: hit is NULL.");
		return (false);
	}
	elem = ft_lstnew(hit);
	if (!elem)
	{
		ft_error(2, "add_hit_record: cannnot put hit_record into the list.");
		return (false);
	}
	ft_lstadd_back(records, elem);
	return (true);
}

t_hit_record	*get_hit_record(t_list *records, int index)
{
	t_hit_record	*hit;
	t_list			*tmp;
	int				i;

	if (index < 0 || index > ft_lstsize(records))
	{
		ft_error(1, "get_hit_record: index not in range.");
		return (NULL);
	}
	tmp = records;
	i = 0;
	while (i < index)
	{
		i++;
		tmp = tmp->next;
	}
	hit = (t_hit_record *) tmp->content;
	return (hit);
}

t_hit_record	*get_closest_hit(t_list *hits, float pos[VEC3_SIZE])
{
	t_hit_record	*closest_hit;
	t_list			*tmp;
	float			dis_vec[VEC3_SIZE];
	float			distance;
	float			min;

	closest_hit = (t_hit_record *) hits->content;
	min = INFINITY;
	tmp = hits;
	while (tmp)
	{
		distance = vec3_length(
				vec3_sub(((t_hit_record *) tmp->content)->pos, pos, dis_vec));
		if (distance < min)
		{
			min = distance;
			closest_hit = (t_hit_record *) tmp->content;
		}
		tmp = tmp->next;
	}
	return (closest_hit);
}
