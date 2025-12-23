/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:06:18 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/23 12:43:18 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

/*
- map: the map grid and player state
- textures: file paths for the wall textures
- floor_color/ceil_color: int arrays for R,G,B
*/
typedef struct s_scene
{
	t_map	map;
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	char	*texture_bonus;
	int		floor_color[3];
	int		ceil_color[3];
}	t_scene;

/* Utils */
void	error_exit(char *msg);
void	free_tab(char **tab);
void	check_extension(char *file);
void	strip_newline(char *s);
void	normalize_map(t_map *map);
void	transfer_list_to_grid(t_map *map, t_list *head);
int		is_empty_line(char *line);

/* Parsing & validation */
void	parse(char *file, t_scene *scene);
void	parse_scene(char *file, t_scene *scene);
void	parse_scene_line(char *line, t_scene *scene);
void	validate_map(t_map *map);
void	check_metadata_completeness(t_scene *scene);

#endif
