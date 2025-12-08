/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:07:32 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/08 09:12:56 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** pad_line
** Allocates a new string of size 'width'.
** Copies the original line content into it.
** Fills the remainder of the new string with spaces.
** Example: "1101" becomes "1101    " if width is 8.
*/
static char	*pad_line(char *line, int width)
{
	char	*new_line;
	int		len;
	int		i;

	new_line = malloc(sizeof(char) * (width + 1));
	if (!new_line)
		error_exit("Malloc failed");
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

/*
** normalize_map
** 1. Finds the maximum width among all rows.
** 2. Replaces every row with a "padded" version of itself.
** This transforms a ragged map into a perfect rectangle, simplifying validation.
*/
/* Normalization: It finds the longest line and pads all shorter lines with spaces. 
This creates a perfect rectangle, making the "wall check" logic strictly based on 
array indices without fearing segfaults on ragged lines. */
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

/*
** read_file_to_grid
** Uses Get_Next_Line to read the file line by line.
** - Stores lines in a linked list first (because we don't know the height yet).
** - Calculates height using ft_lstsize.
** - Allocates the exact char **grid array.
** - Transfers data from the list to the array and frees the list nodes.
*/
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
		ft_lstadd_front(&head, ft_lstnew(line));
	}
	map->height = ft_lstsize(head);
	if (map->height == 0)
		error_exit("Empty map file");
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		error_exit("Malloc failed");
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

/*
** parse_map
** Driver function for the parsing process.
** 1. Opens the file.
** 2. Reads content into the struct.
** 3. Closes the file.
** 4. Normalizes (pads) the map lines.
*/
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

/*
** print_success
** A debug helper to print the parsed map state if validation passes.
** It shows the normalized (rectangular) map with padded spaces.
*/
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
	free_tab(map.grid);
	return (0);
}
