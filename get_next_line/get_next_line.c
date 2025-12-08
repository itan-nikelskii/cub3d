/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:54:11 by inikelsk          #+#    #+#             */
/*   Updated: 2025/05/24 14:15:27 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* read_and_append keeps line growing until a newline is found (managed by
extract_line_and_remainder); on a newline or EOF, the line is returned. On
EOF, whatever is left is returned; if nothing is left or an error occurs, 
the static buffer is cleaned up and NULL is returned. */
char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;
	int			read_status;

	if (fd < 0 || BUFFER_SIZE <= 0)
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

/* 
#include <fcntl.h>     // for open()
#include <stdio.h>
int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
	while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
		free(line);
    }
	close(fd);
    return (0);
}  
*/
