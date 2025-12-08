/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:01:25 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 09:08:00 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

/*
** t_map structure
** Stores all information regarding the parsed map.
**
** - grid: A 2D array (array of strings) representing the map.
** grid[y][x] accesses the character at row y, column x.
** - height: The total number of rows (lines) in the map.
** - width: The length of the longest row. All rows are padded to this length.
** - player_count: A counter used during validation to ensure exactly 1 player exists.
** - player_dir: The character ('N', 'S', 'E', 'W') indicating starting orientation.
** - p_x: The X coordinate (column index) where the player starts.
** - p_y: The Y coordinate (row index) where the player starts.
*/
typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_count;
	char	player_dir;
	int		p_x;
	int		p_y;
}	t_map;

void	error_exit(char *msg);
void	check_extension(char *file);
void	parse_map(char *file, t_map *map);
void	validate_map(t_map *map);
void	free_tab(char **tab);

#endif
