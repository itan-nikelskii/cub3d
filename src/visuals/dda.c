/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:28:31 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/30 13:05:09 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "visualisation.h"
#include "parser.h" // for s_map

/** Returns which side was hit as an enum, based on whether the step to take
 * in that direction was positive or not, and whether X or Y was passed.
 */
static int	determine_side_hit(int take_step, int x_or_y)
{
	if (x_or_y == X)
	{
		if (take_step > 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (take_step > 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

/** Make sure the coordinates passed are within map bounds. If not,
 * return 'false'.
 * @param map_square Grid coordinates in an array containing X and Y.
 * @param map Information map struct, needed for width and height.
*/
static bool	check_in_bounds(double *map_square, t_map *map)
{
	if (map_square[Y] < 0 || map_square[Y] > map->height - 1 \
|| map_square[X] < 0 || map_square[X] > map->width - 1)
		return (false);
	return (true);
}

/** Perform the digital differential analyzer: keep moving small steps towards
 * the closest wall until it is reached. Then return whether that map is north,
 * south, east or west (using an enum).
 */
int	perform_dda(t_ray *ray_info, t_map *map)
{
	int	wall_hit;
	int	side;

	wall_hit = 0;
	while (wall_hit == 0)
	{
		if (ray_info->side_distance.x < ray_info->side_distance.y)
		{
			ray_info->side_distance.x += ray_info->delta_distance[X];
			ray_info->map_square[X] += ray_info->take_step[X];
			side = determine_side_hit(ray_info->take_step[X], X);
		}
		else
		{
			ray_info->side_distance.y += ray_info->delta_distance[Y];
			ray_info->map_square[Y] += ray_info->take_step[Y];
			side = determine_side_hit(ray_info->take_step[Y], Y);
		}
		if (!check_in_bounds(ray_info->map_square, map))
			break ;
		if (map->grid[(int)ray_info->map_square[Y]][(int)ray_info->\
map_square[X]] == '1')
			wall_hit = 1;
	}
	return (side);
}
