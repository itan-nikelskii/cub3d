/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:42:29 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/09 14:16:48 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Iterate through the raw grid to find the longest line. This is used later 
   to pad shorter lines with spaces so the map becomes a perfect rectangle. */
static int	get_max_width(char **grid, int height)
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

/* Pad all lines shorter than max width with spaces: allocate a new string of
   size width, copy the original line into it, and fill the remainder with spaces
   (example: "1101" becomes "1101    " if width is 8). */
static char	*pad_line(char *line, int width)
{
	char	*new_line;
	int		len;
	int		i;

	new_line = malloc(sizeof(char) * (width + 1));
	if (!new_line)
		error_exit("malloc failure");
	len = ft_strlen(line);
	i = 0;
	while (i < width)
	{
		if (i < len && line[i] != '\n')
			new_line[i] = line[i];
		else
			new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

/* Normalization: find the longest line and pad all shorter lines with spaces. 
   This creates a perfect rectangle, making the wall check logic strictly based
   on array indices. */
void	normalize_map(t_map *map)
{
	int	i;
	int	w;

	w = get_max_width(map->grid, map->height);
	map->width = w;
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = pad_line(map->grid[i], w);
		i++;
	}
}

/* Transfer the linked list to the char **grid array. */
void	transfer_list_to_grid(t_map *map, t_list *head)
{
	t_list	*node;
	int		i;

	map->height = ft_lstsize(head);
	if (map->height == 0)
		error_exit("Map content missing");
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		error_exit("malloc failure");
	map->grid[map->height] = NULL;
	i = map->height - 1;
	while (head)
	{
		node = head->next;
		map->grid[i--] = (char *)head->content;
		free(head);
		head = node;
	}
}
