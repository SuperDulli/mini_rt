/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:43:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/11 14:55:41 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_maxf(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float	ft_minf(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
