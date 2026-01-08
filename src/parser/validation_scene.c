/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:13:48 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/08 13:05:28 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h> // for open()

/* Convert and validate a color string "255". */
static int	parse_single_color(char *s)
{
	int	val;
	int	i;

	i = 0;
	if (!s[i])
		error_exit("Invalid color format (empty)");
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			error_exit("Invalid color format (non-digit)");
		i++;
	}
	val = ft_atoi(s);
	if (val < 0 || val > 255)
		error_exit("Color value out of range (0-255)");
	return (val);
}

/* Parse "R,G,B", validate format, and store it in an int array. */
static void	parse_rgb(char *args, int *dest)
{
	char	**parts;
	int		i;
	char	*trimmed;

	if (dest[0] != -1)
		error_exit("Potential duplicate color definition");
	parts = ft_split(args, ',');
	if (!parts)
		error_exit("malloc failure");
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
		error_exit("Invalid color format (must be R,G,B)");
	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(parts[i], " \t\n\v\f\r");
		dest[i] = parse_single_color(trimmed);
		free(trimmed);
		i++;
	}
	free_tab(parts);
}

/* Verify that the texture file exists, is readable, and is not a directory. */
static void	validate_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Invalid texture path (missing or permission denied)");
	close(fd);
	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		error_exit("Invalid texture path (is a directory)");
	}
}

/* Parse and store texture path, checking for duplicates and file validity. */
static void	parse_texture(char *path, char **dest)
{
	if (*dest && *dest != NULL)
		error_exit("Duplicate texture definition");
	*dest = ft_strtrim(path, " \t\n\v\f\r");
	if (!*dest)
		error_exit("malloc failure");
	validate_texture_path(*dest);
}

/* Dispatcher for metadata lines. */
void	parse_scene_line(char *line, t_scene *scene)
{
	char	*ptr;

	ptr = line;
	while (ft_isspace(*ptr))
		ptr++;
	if (ft_strncmp(ptr, "NO", 2) == 0)
		parse_texture(ptr + 2, &scene->texture_north);
	else if (ft_strncmp(ptr, "SO", 2) == 0)
		parse_texture(ptr + 2, &scene->texture_south);
	else if (ft_strncmp(ptr, "WE", 2) == 0)
		parse_texture(ptr + 2, &scene->texture_west);
	else if (ft_strncmp(ptr, "EA", 2) == 0)
		parse_texture(ptr + 2, &scene->texture_east);
	else if (ft_strncmp(ptr, "BO", 2) == 0)
		parse_texture(ptr + 2, &scene->texture_bonus);
	else if (ft_strncmp(ptr, "F", 1) == 0)
		parse_rgb(ptr + 1, scene->floor_color);
	else if (ft_strncmp(ptr, "C", 1) == 0)
		parse_rgb(ptr + 1, scene->ceil_color);
	free(line);
}
