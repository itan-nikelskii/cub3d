/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:03:59 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 09:09:16 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

/*
** free_tab
** Frees a 2D array of strings (char **).
** It first iterates through the array freeing every string,
** then frees the array pointer itself.
*/
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

void	check_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
		error_exit("Invalid file extension. Use .cub");
}

/*
** get_max_width
** Iterates through the raw grid to find the longest line.
** This is used later to pad shorter lines with spaces so the map
** becomes a perfect rectangle.
*/
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
