/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:33:39 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/22 14:07:01 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <math.h>
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
		return (MLX_FAIL);
	}
	return (NO_ERROR);
}

/** Creates an image to draw on, then performs calculations for each vertical
 * stripe of the screen and draws a textured line on the image, and finally
 * displays the image.
 * Most calculations explained inside the specific functions. The calculations
 * inside this function determine the distance to the closest wall from the
 * camera plane in the direction of the ray. 
*/
int	display_cubes(t_data *data)
{
	int		x;
	t_ray	ray_info;

	data->visuals.cubes = mlx_new_image(data->visuals.mlx, SCREEN_WIDTH,
		SCREEN_HEIGHT);
	if (!data->visuals.cubes)
		return (printf("New image fail\n"), MLX_FAIL); // cleanup!!!!
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		set_ray_starting_point(&ray_info, data->player, x);
		set_delta_distances(&ray_info);
		set_ray_info(&ray_info, data->player);
		ray_info.side = perform_dda(&ray_info, &data->scene.map);
		if (ray_info.side == EAST || ray_info.side == WEST)
			ray_info.wall_distance = (ray_info.map_square[X] - data->player.\
x_grid + (1 - ray_info.take_step[X]) / 2) / ray_info.ray_direction.x;
		else
			ray_info.wall_distance = (ray_info.map_square[Y] - data->player.\
y_grid + (1 - ray_info.take_step[Y]) / 2) / ray_info.ray_direction.y;
		draw_texture_line(data, ray_info, data->visuals.cubes, x);
		x++;
	}
	if (mlx_image_to_window(data->visuals.mlx, data->visuals.cubes, 0, 0) == -1)
		return (printf("image to window fail\n"), MLX_FAIL); // cleanup!!
	return (NO_ERROR);
}

/** Set up an image, draw the floor and ceiling in this image, and then draw 
 * the cube visuals at the start position.
*/
int	visualisation(t_data *data)
{
	data->visuals.background = mlx_new_image(data->visuals.mlx, SCREEN_WIDTH,
		SCREEN_HEIGHT);
	if (!data->visuals.background)
		return (MLX_FAIL);
	if (display_floor_ceiling(&data->visuals) != NO_ERROR)
	{
		printf("Failed to display background.\n");
		clean_up(data, true);
		mlx_terminate(data->visuals.mlx);
		return (MLX_FAIL);
	}
	display_cubes(data);
	return (NO_ERROR);
}
