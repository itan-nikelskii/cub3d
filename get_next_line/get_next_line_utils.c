/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:54:40 by inikelsk          #+#    #+#             */
/*   Updated: 2025/05/24 13:41:17 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Return the length of string s. */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

/* Duplicate string s and return the result, or NULL on malloc failure. */
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/* Allocate memory and return a new string that is the result of concatenating
s1 and s2. On failure, return NULL. Note +1 on malloc for \0. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	final_len;
	size_t	i;
	size_t	j;
	char	*result;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	final_len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc((final_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		result[i++] = s1[j++];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

/* Scan *line for newline (\n); if found:
- extract everything up to and including \n and return it as the next line;
- save everything after \n back into *line for the next call to get_next_line.
If no newline is found, return NULL = need to read more.
On EOF, return everything left in *line. 
Note about **line: double pointer because the function modifies the original 
line pointer (passing it as char * would only allow modifying the contents). */
char	*extract_line_and_remainder(char **line)
{
	int		i;
	int		j;
	char	*next_line;
	char	*remainder;

	if (!*line || !**line)
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
ssize_t	read_and_append(int fd, char **line)
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
