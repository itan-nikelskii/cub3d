/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:06:18 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/09 10:31:23 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "../include/definitions.h"

/* Utils */
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
