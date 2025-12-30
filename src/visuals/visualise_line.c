/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualise_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:04:26 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/30 15:37:43 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"
#include "cub3d.h"
#include <math.h> // for floor()

/** Returns the correct texture from the textures struct, depending on which
 * side of the cube the ray hit.
 */
static mlx_texture_t	*choose_texture(t_ray ray, t_textures textures,
	t_data *data)
{
	mlx_texture_t	*relevant_texture;

	if (ray.side == NORTH)
	{
		relevant_texture = textures.north_texture;
		if (data->bonus_included && data->time % 2000 > 1000)
			relevant_texture = textures.bonus_texture;
	}
	if (ray.side == EAST)
		relevant_texture = textures.east_texture;
	if (ray.side == SOUTH)
		relevant_texture = textures.south_texture;
	if (ray.side == WEST)
		relevant_texture = textures.west_texture;
	return (relevant_texture);
}

/** Calculates where the wall was hit. For example, if the ray hits the middle
 * of the wall, the wall_fraction would be 0.5. By subtracting the floor of the
 * calculated value, only the fraction remains, and the full walls that came 
 * before this wall don't matter.
 * @param player Player struct for grid coordinates.
 * @param ray Ray struct to store wall structure, and to retrieve distance from
 * wall and direction of the ray.
 */
static void	calc_wall_fraction(t_player player, t_ray *ray)
{
	if (ray->side == WEST)
		ray->wall_fraction = player.y_grid + ray->wall_distance * \
ray->ray_direction.y;
	else if (ray->side == EAST)
		ray->wall_fraction = 1 - (player.y_grid + ray->wall_distance * \
ray->ray_direction.y);
	else if (ray->side == NORTH)
		ray->wall_fraction = 1 - (player.x_grid + ray->wall_distance * \
ray->ray_direction.x);
	else
		ray->wall_fraction = player.x_grid + ray->wall_distance * \
ray->ray_direction.x;
	ray->wall_fraction -= floor(ray->wall_fraction);
}

/** Stores the height, lowest point and highest point of the vertical line that
 * will be drawn on screen to represent the slice of cube drawn by the ray.
 */
static void	calc_vertical_line_info(t_ray *ray)
{
	// ray->line_height = (float)fabs(SCREEN_HEIGHT / ray->wall_distance);
	// ray->highest_point = (int)ray->line_height / 2 + SCREEN_HEIGHT / 2;
	// ray->lowest_point = -(int)ray->line_height / 2 + SCREEN_HEIGHT / 2;
	ray->line_height = (int)fabs(SCREEN_HEIGHT / ray->wall_distance);
	ray->lowest_point = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
}

/** Draw a vertical line based on the distance from the wall. Determine which
 * texture to use, the lowest and highest point of the cube line on the screen, 
 * and which horizontal slice of the cube to draw. Placing pixels is done by
 * starting at the lowest pixel of the line and iterating up. Which pixel from
 * the texture to use is determined using the fraction of wall hit and taking
 * that same fraction from the texture.
 * @param data Game data struct, needed for player and textures.
 * @param ray Ray struct.
 * @param cubes Image of all the cubes.
 * @param x Horizontal index of the screen.
*/
void	draw_texture_line(t_data *data, t_ray ray, mlx_image_t *cubes, int x)
{
	mlx_texture_t	*texture;
	float			pixel_index;
	int				i;

	texture = choose_texture(ray, data->textures, data);
	calc_vertical_line_info(&ray);
	// if (x > 510 && x < 514)
	// {
	// 	printf("highest: %d lowest: %d\n", ray.highest_point, ray.lowest_point);
	// }
	calc_wall_fraction(data->player, &ray);
	i = 0;
	if (ray.lowest_point < 0)
	{
		i = i - ray.lowest_point;
		ray.lowest_point = 0;
	}
	while (i <= (int)ray.line_height)
	{
		if (ray.lowest_point >= SCREEN_HEIGHT - 1)
			return ;
// 		pixel_index = 4 * (ray.wall_fraction * (texture->width) + \
// ((texture->width) * (int)(i * (texture->height) / (int)ray.line_height)));
		pixel_index = 4 * (ray.wall_fraction * (texture->width) + \
((texture->width) * (i * (texture->height) / (int)ray.line_height)));
		pixel_index = pass_red_index((int)pixel_index);
		mlx_put_pixel(cubes, x, ray.lowest_point,
			find_pixel_colour(texture, (int)pixel_index));
		ray.lowest_point++;
		i++;
	}
}
