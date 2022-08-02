/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:03:00 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/02 18:50:46 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	str_delete(char **str_pointer)
{
	if (str_pointer && *str_pointer)
	{
		free(*str_pointer);
		*str_pointer = NULL;
	}
}

/*
* Description
*	Creates the output line and saves potential leftovers.
*	Leftovers are everthing after the first newline.
*
* Parameters
*	#1. a pointer to a pointer to a string that holds the file contents that
*	where not yet put out
*
* Return Values
*	the output line, or
*	NULL if an allocation fails
*/
static char	*create_output(char **m)
{
	char	*line;
	size_t	len;
	char	*tmp;

	len = 0;
	while ((*m)[len] != '\n' && (*m)[len] != '\0')
		len++;
	if ((*m)[len] == '\n')
	{
		line = ft_substr((*m), 0, len + 1);
		tmp = ft_strdup(&((*m)[len + 1]));
		free(*m);
		if (!tmp)
			return (NULL);
		*m = tmp;
		if ((*m)[0] == '\0')
			str_delete(m);
	}
	else
	{
		line = ft_strdup(*m);
		str_delete(m);
	}
	return (line);
}

static char	*output(char **m, ssize_t bytes_read, char *buffer)
{
	free(buffer);
	if (!(*m) || bytes_read < 0)
		return (NULL);
	return (create_output(m));
}

/*
* Description
*	Read a line from a file and returns it.
*	Uses a static variable to keep track of leftovers between function calls.
*	Stores leftovers from diffrent files in an array.
*	It reads until a newline character is found to be read or the end of the file
*	is reached.
*
* Parameters
*	#1. File descriptor to read from
*
* Return Values
*	the read line (including the newline if there is one in the file), or
*	NULL if there is nothing else to read or an error occurred.
*/
char	*get_next_line(int fd)
{
	char		*buffer;
	char		*tmp;
	static char	*memory[MAX_FD];
	ssize_t		bytes_read;

	buffer = (char *) malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!memory[fd])
			memory[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(memory[fd], buffer);
			free(memory[fd]);
			memory[fd] = tmp;
		}
		if (ft_strchr(memory[fd], '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (output(&memory[fd], bytes_read, buffer));
}
