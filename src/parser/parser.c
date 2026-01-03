/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:07:32 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/03 17:39:49 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if the scene struct has all required metadata. */
void	check_metadata_completeness(t_scene *scene)
{
	if (!scene->texture_north || !scene->texture_south || !scene->texture_west
		|| !scene->texture_east)
		error_exit("Issue with texture(s)");
	if (scene->floor_color[0] == -1 || scene->ceil_color[0] == -1)
		error_exit("Issue with color(s)");
}

/* Process a metadata line. Return 1 if the line was empty (and freed) or 
   metadata (and parsed) => the main loop should continue; return 0 if the 
   line was not metadata => must be the start of the map. */
static int	process_metadata(char *line, t_scene *scene)
{
	if (is_empty_line(line))
	{
		free(line);
		return (1);
	}
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "BO", 2) == 0 || ft_strncmp(line, "F", 1) == 0
		|| ft_strncmp(line, "C", 1) == 0)
	{
		parse_scene_line(line, scene);
		return (1);
	}
	return (0);
}

/* Read the scene file line by line. If a line is not metadata and not empty, 
   assume the start of the map. Then read the map and store lines in a linked 
   list. Finally, transfer the list to the map->grid array. */
static void	read_file_content(int fd, t_scene *scene)
{
	char	*line;
	t_list	*map_head;
	int		in_map;

	map_head = NULL;
	in_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!in_map && process_metadata(line, scene))
			continue ;
		if (!in_map)
		{
			in_map = 1;
			check_metadata_completeness(scene);
		}
		strip_newline(line);
		ft_lstadd_front(&map_head, ft_lstnew(line));
	}
	transfer_list_to_grid(&scene->map, map_head);
}

/* Initialize all t_scene entries (map + metadata). */
static void	init_scene(t_scene *scene)
{
	scene->map.grid = NULL;
	scene->map.height = 0;
	scene->map.width = 0;
	scene->map.player_count = 0;
	scene->map.player_dir = 0;
	scene->texture_north = NULL;
	scene->texture_south = NULL;
	scene->texture_west = NULL;
	scene->texture_east = NULL;
	scene->texture_bonus = NULL;
	scene->floor_color[0] = -1;
	scene->ceil_color[0] = -1;
}

/* Top-level parsing entry point. Initialize scene, open the file, parse file 
   content, validate scene completeness, and normalize and validate the map. */
void	parse(char *file, t_scene *scene)
{
	int	fd;

	check_extension(file);
	init_scene(scene);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	read_file_content(fd, scene);
	close(fd);
	check_metadata_completeness(scene);
	normalize_map(&scene->map);
	validate_map(&scene->map);
}
