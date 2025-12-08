/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:07:32 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 15:05:55 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
static void	normalize_map(t_map *map)
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

/* Read the map file line by line, store lines in a linked list first (because 
   we don't know the height yet), and calculate the height using ft_lstsize.
   Then allocate the grid array, transfer data from the list and free it. */
   // TODO: fix too many lines
static void	read_file_to_grid(int fd, t_map *map)
{
	char	*line;
	t_list	*head;
	t_list	*node;
	int		i;

	head = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		strip_newline(line);
		ft_lstadd_front(&head, ft_lstnew(line));
	}
	map->height = ft_lstsize(head);
	if (map->height == 0)
		error_exit("Empty map file");
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

/* Parser: open the file, read the content into the map struct, close the file,
   normalize the map lines. */
void	parse_map(char *file, t_map *map)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	map->player_count = 0;
	map->height = 0;
	map->width = 0;
	read_file_to_grid(fd, map);
	close(fd);
	normalize_map(map);
}

/* Initialize all t_map struct entries. */
static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->player_count = 0;
	map->player_dir = 0;
	map->p_x = 0;
	map->p_y = 0;
}

/* ----------- BELOW ONLY DEBUG STUFF FOR TESTING THe PARSER PART ----------- */

/* A debug helper to print the parsed map state if validation passes. Just shows
   the normalized (rectangular) map with padded spaces. */
static void	print_success(t_map *map)
{
	int	i;

	printf("Map valid!\n");
	printf("Dimensions: %dx%d\n", map->width, map->height);
	printf("Player: %c at (%d, %d)\n", map->player_dir, map->p_x, map->p_y);
	printf("Map Content:\n");
	i = 0;
	while (map->grid[i])
	{
		printf("|%s|\n", map->grid[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map_path.cub>");
	check_extension(argv[1]);
	init_map(&map);
	parse_map(argv[1], &map);
	validate_map(&map);
	print_success(&map);

	visualisation_section(&map); // better function name incoming, but this leads to manon's former main

	free_tab(map.grid);
	return (0);
}
