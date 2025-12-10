/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:07:32 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/10 12:28:19 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Read the scene file line by line. If a line is not metadata and not empty, 
   assume the start of the map. Then read the map and store lines in a linked 
   list. Finally, transfer the list to the map->grid array. */ // TODO: fix too many lines
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
		if (!in_map)
		{
			if (is_empty_line(line))
				free(line);
			else if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
				|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
				|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
				parse_scene_line(line, scene);
			else
			{
				in_map = 1;
				check_metadata_completeness(scene); // must have all textures before map
				strip_newline(line);
				ft_lstadd_front(&map_head, ft_lstnew(line));
			}
		}
		else
		{
			strip_newline(line);
			ft_lstadd_front(&map_head, ft_lstnew(line));
		}
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
	scene->floor_color[0] = -1;
	scene->ceil_color[0] = -1;
}

/* ----------- BELOW ONLY DEBUG STUFF FOR TESTING THe PARSER PART ----------- */

/* A debug helper to print the full parsed scene if validation passes. TODO: delete! */
static void	print_success(t_scene *scene)
{
	t_map	*map;
	int		i;

	map = &scene->map;
	printf("\n--- Scene validation successful! ---\n\n");
	printf("--- Textures ---\n");
	printf("NO (North): %s\n", scene->texture_north);
	printf("SO (South): %s\n", scene->texture_south);
	printf("WE (West):  %s\n", scene->texture_west);
	printf("EA (East):  %s\n", scene->texture_east);
	printf("\n--- Colors ---\n");
	printf("Floor: RGB(%d, %d, %d)\n", scene->floor_color[0], scene->floor_color[1],
		scene->floor_color[2]);
	printf("Ceiling: RGB(%d, %d, %d)\n", scene->ceil_color[0], scene->ceil_color[1],
		scene->ceil_color[2]);
	printf("\n--- Map ---\n");
	printf("Dimensions: %dx%d\n", map->width, map->height);
	printf("Player: '%c' at position (%d, %d)\n", map->player_dir, map->p_x, map->p_y);
	printf("\nMap Content:\n");
	i = 0;
	while (map->grid[i])
	{
		printf("|%s|\n", map->grid[i]);
		i++;
	}
	printf("\n");
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
	print_success(scene); // TODO: debug only, delete later
}
