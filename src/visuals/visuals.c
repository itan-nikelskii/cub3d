/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:33:39 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/22 11:50:10 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "visualisation.h"
#include "cub3d.h"

/** TESTING ONLY */
void print_player_info(t_player player)
{
	printf("player struct location x=%i & y=%i. direction: x=%f & y=%f\n", 
	player.x_pixels, player.y_pixels, player.facing.x, player.facing.y);
}

/** REAL CODE FROM HERE */

/** Uses put_pixel to colour the top half of the image to ceiling colours
 * and the bottom half to floor colours.
 */
int	display_floor_ceiling(t_visuals *visuals)
{
	int x;
	int y;

	y = 0;
	while (y < (int)visuals->background->height / 2)
	{
		x = -1;
		while (++x < (int)visuals->background->width)
			mlx_put_pixel(visuals->background, x, y, visuals->ceiling_colour);
		y++;
	}
	while (y < (int)visuals->background->height)
	{
		x = -1;
		while (++x < (int)visuals->background->width)
			mlx_put_pixel(visuals->background, x, y, visuals->floor_colour);
		y++;
	}
	if (mlx_image_to_window(visuals->mlx, visuals->background, 0, 0) == -1)
	{
		mlx_delete_image(visuals->mlx, visuals->background);
		error_exit("MLX: failed to display background.");
	}
	return (NO_ERROR);
}

/** Returns the correct texture from the textures struct, depending on which
 * side of the cube the ray hit.
 */
mlx_texture_t	*choose_texture(t_ray ray, t_textures textures)
{
	mlx_texture_t 	*relevant_texture;

	if (ray.side == NORTH)
		relevant_texture = textures.north_texture;
	if (ray.side == EAST)
		relevant_texture = textures.east_texture;
	if (ray.side == SOUTH)
		relevant_texture = textures.south_texture;
	if (ray.side == WEST)
		relevant_texture = textures.west_texture;
	return (relevant_texture);
}

/* Return the R index of the relevant pixel, not G, B or A index. */
float	pass_red_index(pixel_index)
{
	if ((int)pixel_index % 4 == 0)
		return (pixel_index);
	if ((int)pixel_index % 4 == 1)
		return ((int)pixel_index - 1);
	if ((int)pixel_index % 4 == 2)
		return ((int)pixel_index - 2);
	if ((int)pixel_index % 4 == 3)
		return ((int)pixel_index - 3);
	return (pixel_index);
}

/** Calculates where the wall was hit. For example, if the ray hits the middle
 * of the wall, the wall_fraction would be 0.5. By subtracting the floor of the
 * calculated value, only the fraction remains, and the full walls that came 
 * before this wall don't matter.
 * @param player Player struct for grid coordinates.
 * @param ray Ray struct to store wall structure, and to retrieve distance from
 * wall and direction of the ray.
 */
void	calc_wall_fraction(t_player player, t_ray *ray)
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
void	calc_vertical_line_info(t_ray *ray)
{
	ray->line_height = (float)fabs(SCREEN_HEIGHT / ray->wall_distance);
	ray->highest_point = (int)ray->line_height / 2 + SCREEN_HEIGHT / 2;
	ray->lowest_point = -(int)ray->line_height / 2 + SCREEN_HEIGHT / 2;
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
	mlx_texture_t 	*texture;
	float			pixel_index;
	int				i;

	texture = choose_texture(ray, data->textures);
	calc_vertical_line_info(&ray);
	calc_wall_fraction(data->player, &ray);
	i = 0;
	if (ray.lowest_point < 0)
	{
		i = i - ray.lowest_point;
		ray.lowest_point = 0;
	}
	while (i < (int)ray.line_height)
	{
		if (ray.lowest_point >= SCREEN_HEIGHT)
			return ;
		pixel_index = 4 * (ray.wall_fraction * (texture->width) + \
((texture->width) * (int)(i * (texture->height) / (int)ray.line_height)));
		pixel_index = pass_red_index(pixel_index);
		mlx_put_pixel(cubes, x, ray.lowest_point, 
			find_pixel_colour(texture, (int)pixel_index));
		ray.lowest_point++;
		i++;
	}
}

/** Perform the digital differential analyzer: keep moving small steps until
 * a wall is reached. Then return whether that map is north, south, east or west.
 */
int	perform_dda(t_ray *ray_info, t_map *map)
{
	int	wall_hit;
	int	side; // enum with N E S W

	wall_hit = 0;
	while (wall_hit == 0)
		{
			// jump to next square -> either X or Y direction
			if (ray_info->side_distance.x < ray_info->side_distance.y)
			{
				ray_info->side_distance.x += ray_info->delta_distance[X];
				ray_info->map_square[X] += ray_info->take_step[X];
				if (ray_info->take_step[X] > 0)
					side = WEST;
				else
					side = EAST;
			}
			else
			{
				ray_info->side_distance.y += ray_info->delta_distance[Y];
				ray_info->map_square[Y] += ray_info->take_step[Y];
				if (ray_info->take_step[Y] > 0)
					side = NORTH;
				else
					side = SOUTH;
			}
			// check hit
			if (map->grid[(int)ray_info->map_square[Y]][(int)ray_info->map_square[X]] == '1')
				wall_hit = 1;
		}
	// printf("hit wall with coordinates %i / %i\n", (int)ray_info->map_square[X], (int)ray_info->map_square[Y]);
	return (side);
}

/** Return the x and y coordinates of the cube in the map grid that was hit
 * by the ray.
 */
t_coordinates find_cube_hit(t_ray ray_info, t_player player, int x, t_map *map)
{
	t_coordinates	cube_hit;
	int				wall_hit;

	set_ray_starting_point(&ray_info, player, x);
	set_delta_distances(&ray_info);
	set_ray_info(&ray_info, player);
	wall_hit = 0;
	while (wall_hit == 0)
		{
			// jump to next square -> either X or Y direction
			if (ray_info.side_distance.x < ray_info.side_distance.y)
			{
				ray_info.side_distance.x += ray_info.delta_distance[X];
				ray_info.map_square[X] += ray_info.take_step[X];
			}
			else
			{
				ray_info.side_distance.y += ray_info.delta_distance[Y];
				ray_info.map_square[Y] += ray_info.take_step[Y];
			}
			// check hit
			if (map->grid[(int)ray_info.map_square[Y]][(int)ray_info.map_square[X]] == '1')
				wall_hit = 1;
		}
	// printf("hit wall with coordinates %i / %i\n", (int)ray_info->map_square[X], (int)ray_info->map_square[Y]);
	cube_hit.x = ray_info.map_square[X];
	cube_hit.y = ray_info.map_square[Y];
	return (cube_hit);
}

/** Function to set up the vertical rays. */
int	display_cubes(t_data *data)
{
	int 			x; // index for each vertical stripe
	t_ray			ray_info;
	t_player		player = data->player; // just use data->player? but carefully

	if (data->visuals.cubes)
		mlx_delete_image(data->visuals.mlx, data->visuals.cubes);
	data->visuals.cubes = mlx_new_image(data->visuals.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->visuals.cubes)
		return (printf("new image err\n"), -1);

	// printf("display cubes! player y %d & %f\n", player.y_pixels, player.y_grid);

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		set_ray_starting_point(&ray_info, player, x);
		// determine length of ray from one side to the next
		set_delta_distances(&ray_info);
		// for this next part it's important both player pixel location & player
		// grid coordinates are up to date -> handle that in movement function
		set_ray_info(&ray_info, player);
		ray_info.side = perform_dda(&ray_info, &data->scene.map);
		// calculations for camera: shortest distance from camera plane to wall hit
		// take one step back since you've already hit a wall
		if (ray_info.side == EAST || ray_info.side == WEST)
			ray_info.wall_distance = (ray_info.map_square[X] - player.x_grid + (1 - ray_info.take_step[X]) / 2) / ray_info.ray_direction.x;
		else
			ray_info.wall_distance = (ray_info.map_square[Y] - player.y_grid + (1 - ray_info.take_step[Y]) / 2) / ray_info.ray_direction.y;
		ray_info.cube_hit.x = ray_info.map_square[X];
		ray_info.cube_hit.y = ray_info.map_square[Y];	
		// ray_info.cube_hit = find_cube_hit(ray_info, player, x, &data->scene.map);
		// integrate find_cube_hit more so i'm not doing computing work twice
		draw_texture_line(data, ray_info, data->visuals.cubes, x);
		x++;
	}
	mlx_image_to_window(data->visuals.mlx, data->visuals.cubes, 0, 0);
	return (0);
}

/** Set up an image, draw the floor and ceiling in this image, and then draw 
 * the cube visuals at the start position.
*/
int	visualisation(t_data *data)
{
	data->visuals.background = mlx_new_image(data->visuals.mlx, SCREEN_WIDTH,
		SCREEN_HEIGHT);
	if (!data->visuals.background)
		return (1);
	if (display_floor_ceiling(&data->visuals) != NO_ERROR)
		return (1);
	display_cubes(data);
	return (0);
}
