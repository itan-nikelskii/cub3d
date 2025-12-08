/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:03:59 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 14:21:13 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Ensure that the map file extension is ".cub". */
void	check_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)	// this allows ".cub" w/o an actual name, don't know if that should be valid
		error_exit("Invalid file extension. Use .cub");
}

/* Iterate through the raw grid to find the longest line. This is used later 
   to pad shorter lines with spaces so the map becomes a perfect rectangle. */
int	get_max_width(char **grid, int height)
{
	int	max;
	int	i;
	int	len;

	max = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
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
