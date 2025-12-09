/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:03:59 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/09 14:16:45 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Ensure that the map file extension is ".cub". */
void	check_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
		error_exit("Invalid file extension. Use .cub");
}

/* GNL returns each line (except the last one) with a newline; remove it. */
void	strip_newline(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

/* Check if a line contains only whitespace. */
int	is_empty_line(char *line)
{
	while (*line)
	{
		if (!ft_strchr(" \t\n\v\f\r", *line))
			return (0);
		line++;
	}
	return (1);
}
