/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:28 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/19 16:38:20 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h> // for INT_MAX
#include <math.h> // for sqrt()

/** At the start of each loop to determine the pixels on the vertical line of 
 * the screen to draw, set ray_info to contain starting location, 
 * camera_coordinate, and x and y direction.
 */
void	set_ray_starting_point(t_ray *ray_info, t_player player, int x)
{
		ray_info->map_square[X] = (int)player.x_grid;
		ray_info->map_square[Y] = (int)player.y_grid;	

		// which vertical line are we watching
		ray_info->camera_coordinate = 2 * x / (double)SCREEN_WIDTH - 1;
		// direction of the ray in x and y
		ray_info->ray_direction.x = player.facing.x + player.camera_plane.x \
* ray_info->camera_coordinate;
		ray_info->ray_direction.y = player.facing.y + player.camera_plane.y \
* ray_info->camera_coordinate;

// 	if (x == SCREEN_WIDTH / 2)
// 	{
// 		printf("direction x: %f, player facing x: %f, cam plane: %f\n",
// 			ray_info->ray_direction.x, player.facing.x, player.camera_plane.x);
// 	}
}

/** Set delta distance X and Y in the ray struct. */
void	set_delta_distances(t_ray *ray_info)
{
	if (ray_info->ray_direction.x != 0)
	{
		ray_info->delta_distance[X] = sqrt(1 + \
pow(ray_info->ray_direction.y, 2) / pow(ray_info->ray_direction.x, 2));
	}
	else
		ray_info->delta_distance[X] = INT_MAX;
	if (ray_info->ray_direction.y != 0)
	{
		ray_info->delta_distance[Y] = sqrt(1 + \
pow(ray_info->ray_direction.x, 2) / pow(ray_info->ray_direction.y, 2));
	}
	else
		ray_info->delta_distance[Y] = INT_MAX;

	// if (ray_info->camera_coordinate == 0)
	// 	printf("set_delta: delta Y: %f\n", ray_info->delta_distance[Y]);
}

/** Sets the steps that will be taken to 1 or -1, depending on whether the
 * direction is positive or negative, and sets the distance to the nearest
 * side of a cube in the ray direction.
 */
void	set_ray_info(t_ray *ray, t_player player)
{
	if (ray->ray_direction.x < 0)
	{
		ray->take_step[X] = -1;
		ray->side_distance.x = (player.x_grid - ray->map_square[X]) * \
ray->delta_distance[X];
	}
	else
	{
		ray->take_step[X] = 1;
		ray->side_distance.x = (ray->map_square[X] - player.x_grid + 1.0) * \
ray->delta_distance[X];
	}
	if (ray->ray_direction.y < 0)
	{
		ray->take_step[Y] = -1;
		ray->side_distance.y = (player.y_grid - ray->map_square[Y]) * \
ray->delta_distance[Y];
	}
	else
	{
		ray->take_step[Y] = 1;
		ray->side_distance.y = (ray->map_square[Y] - player.y_grid + 1) * \
ray->delta_distance[Y];
	}
}
