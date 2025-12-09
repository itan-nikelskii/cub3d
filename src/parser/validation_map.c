/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:04:43 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/09 14:16:46 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* TODO: documentation */
static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* Scan every char in the grid and:
   1. Check if the char is valid (0, 1, N, S, E, W, space);
   2. If a player is found, save their position and direction;
   3. Ensure there is exactly one player on the map. */
static void	check_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (!ft_strchr("01NSEW ", map->grid[i][j]))
				error_exit("Invalid character in map");
			if (is_player(map->grid[i][j]))
			{
				map->player_count++;
				map->player_dir = map->grid[i][j];
				map->p_x = j;
				map->p_y = i;
			}
			j++;
		}
		i++;
	}
	if (map->player_count != 1)
		error_exit("Must have exactly one player");
}

/* Check if the cell is on the edge of the grid (illegal for floor/player);
   check the 4 neighbors (up + down, left + right); if any neighbor is a space,
   the map is not enclosed. */
static void	check_walkable_cell(t_map *map, int y, int x)
{
	if (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1)
		error_exit("Map is not closed (border)");
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' ')
		error_exit("Map is not closed (hole)");
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		error_exit("Map is not closed (hole)");
}

/* Validation: run character checks; iterate through the grid looking for 
   walkable spaces (0 or player); call check_cell on those walkable spaces
   to ensure they are walled in. */
void	validate_map(t_map *map)
{
	int	i;
	int	j;

	check_chars(map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == '0' || is_player(map->grid[i][j]))
				check_walkable_cell(map, i, j);
			j++;
		}
		i++;
	}
}
