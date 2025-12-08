/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:54:11 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 13:19:59 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Scan *line for newline (\n); if found:
- extract everything up to and including \n and return it as the next line;
- save everything after \n back into *line for the next call to get_next_line.
If no newline is found, return NULL = need to read more.
On EOF, return everything left in *line. 
Note about **line: double pointer because the function modifies the original 
line pointer (passing it as char * would only allow modifying the contents). */
static char	*extract_line_and_remainder(char **line)
{
	int		i;
	int		j;
	char	*next_line;
	char	*remainder;

	if (!line || !*line || !**line)
		return (NULL);
	i = 0;
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] != '\n')
		return (NULL);
	i++;
	next_line = malloc(i + 1);
	if (!next_line)
		return (NULL);
	j = -1;
	while (++j < i)
		next_line[j] = (*line)[j];
	next_line[i] = '\0';
	remainder = ft_strdup(*line + i);
	free(*line);
	*line = remainder;
	return (next_line);
}

/* Read a BUFFER_SIZE chunk from fd and append it to line. Return the number
of bytes read, or -1 on error. */
static ssize_t	read_and_append(int fd, char **line)
{
	char	*buf;
	char	*temp;
	ssize_t	bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free(buf);
		return (bytes);
	}
	buf[bytes] = '\0';
	temp = ft_strjoin(*line, buf);
	free(*line);
	*line = temp;
	free(buf);
	return (bytes);
}

/* read_and_append keeps line growing until a newline is found (managed by
extract_line_and_remainder); on a newline or EOF, the line is returned. On
EOF, whatever is left is returned; if nothing is left or an error occurs, 
the static buffer is cleaned up and NULL is returned. */
char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;
	int			read_status;

	if (fd < 0)
		return (NULL);
	while (1)
	{
		next_line = extract_line_and_remainder(&line);
		if (next_line)
			return (next_line);
		read_status = read_and_append(fd, &line);
		if (read_status <= 0)
			break ;
	}
	if (line && *line && read_status > -1)
	{
		next_line = line;
		line = NULL;
		return (next_line);
	}
	free(line);
	line = NULL;
	return (NULL);
}
