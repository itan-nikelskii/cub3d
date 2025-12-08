/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:03:59 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 10:40:34 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* TODO: documentation; maybe a bool check for whether things need to be freed? */
void	error_exit(char *msg)
{
	printf("Error: %s\n", msg);
	// TODO: free everything here (if it needs to be freed)
	exit(1);
}

/* Free a 2D array of strings (first iterate through the array freeing every 
string, then free the array pointer itself. */
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
