/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:18:49 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/09 12:27:34 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void	exit_fatal(void)
{
	printf("Fatal error.\n");
	// clean up(data);
	exit(1);
}

void	*new(size_t size)
{
	void	*n;

	n = malloc(size);
	if (!n)
		exit_fatal();
	return (n);
}
