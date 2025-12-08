/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:01:25 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 13:42:49 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

/*
- grid: a 2D array representing the map. grid[y][x] = the character at row y, column x.
- height: the total number of rows
- width: the length of the longest row (all rows will be padded to this length)
- player_count: to ensure that exactly 1 player exists
- player_dir: 'N', 'S', 'E', or 'W' for starting orientation
- p_y: the y coordinate (row index) where the player starts
- p_x: the x coordinate (column index) where the player starts
*/
typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_count;
	char	player_dir;
	int		p_y;
	int		p_x;
}	t_map;

void	error_exit(char *msg);
void	check_extension(char *file);
void	parse_map(char *file, t_map *map);
void	validate_map(t_map *map);
void	free_tab(char **tab);
void	strip_newline(char *s);

int		get_max_width(char **grid, int height);

#endif
