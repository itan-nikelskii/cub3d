/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:27:44 by mgroos            #+#    #+#             */
/*   Updated: 2026/01/08 13:15:21 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALISATION_H
# define VISUALISATION_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "cub3d.h"

/** Structure storing information of each vertical ray during raycasting.
 * camera_coordinate: -1 on the far left of the screen, +1 on the far right
 * map_square: grid square that the ray is in
 * side_distance: length of ray from current position to next x or y side
 * delta_distance: 	length of ray from one x or y side to next x or y side
 * take_step: direction to go, either +1 or -1
 * wall_distance: distance between camera plane & wall
 * side: side that got hit: NORTH / SOUTH / EAST / WEST
 * wall_fraction: horizontal fraction of the wall that was hit by the ray
 * highest_point, lowest_point, line_height: info about the texture line drawn
	based on the ray
 */
typedef struct s_ray
{
	double		camera_coordinate;
	t_vector	ray_direction;
	double		map_square[2];
	t_vector	side_distance;
	double		delta_distance[2];
	int			take_step[2];
	double		wall_distance;
	int			side;
	double		wall_fraction;
	int			highest_point;
	int			lowest_point;
	int			line_height;
}	t_ray;

/** To be able to use [X] and [Y] for arrays containing two coordinates, instead
	of relying on remembering [0] and [1]. */
enum e_coordinates
{
	X,
	Y
};

enum e_cardinal_directions
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

int			find_pixel_colour(mlx_texture_t *texture, int i);
void		set_ray_starting_point(t_ray *ray_info, t_player player, int x);
void		set_delta_distances(t_ray *ray_info);
void		set_ray_info(t_ray *ray, t_player player);
float		pass_red_index(int pixel_index);
int			perform_dda(t_ray *ray_info, t_map *map);
void		draw_texture_line(t_data *data, t_ray ray, mlx_image_t *cubes,
				int x);
int			display_cubes(t_data *data);
uint32_t	get_rgba_from_array(int arr[3]);
uint32_t	get_rgba(int r, int g, int b, int a);

#endif