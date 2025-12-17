/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:33:39 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/17 16:07:22 by mgroos           ###   ########.fr       */
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
		return (printf("mlx image to window failed\n"), MLX_FAIL);
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

/** Draw a vertical line based on the distance from the wall. */
void	draw_texture_line(t_ray ray, mlx_image_t *cubes, int x, t_textures textures)
{
	int				highest_point;
	int				lowest_point;
	float			line_height;
	int			 	y;
	mlx_texture_t 	*relevant_texture;
	float			pixel_index;
	int				i;

	line_height = (float)fabs(SCREEN_HEIGHT / ray.wall_distance);
	highest_point = (int)line_height / 2 + SCREEN_HEIGHT / 2;
	lowest_point = -(int)line_height / 2 + SCREEN_HEIGHT / 2;
	relevant_texture = choose_texture(ray, textures);

	y = lowest_point;
	i = 0;

	// real
	while (i < (int)line_height)
	{
		// calculation explanations: 
		/*
		-> 4: because there's 4 pixel indices per actual pixel (R G B and A)
		--> x - cube_width[0] is where you are in the projected cube, horizontally
		--> cube_width[1] - cube_width[0] + 1 is the total width of the projected cube in the final image
		-> so we take the x location in the projected cube, times the ratio of texture width divided by pictured cube width
		-> we do plus the texture width times the ratio of texture height divided by projected height, times i
		--> because if you want to take something from the texture that is not in the top line, you'll have to add the width for every line you go down
		*/

		if (y >= SCREEN_HEIGHT || x >= SCREEN_WIDTH || x < 0) // pretty sure we don't have to worry about x, but just in case
			return ;
		if (y < 0)
		{
			i++;
			y++;
			continue ;
		}

		pixel_index = 4 * ((int)(x - ray.cube_width[0]) * \
(relevant_texture->width) / (ray.cube_width[1] - ray.cube_width[0] + 1) + \
((relevant_texture->width) * (int)(i * (relevant_texture->height) / \
(int)line_height)));

		// printf("pixel index: %f\n", pixel_index);
		/* these checks are to make sure we're always passing the R index, not G B or A. */
		if ((int)pixel_index % 4 == 0)
			mlx_put_pixel(cubes, x, y, find_pixel_colour(relevant_texture, (int)pixel_index));
		if ((int)pixel_index % 4 == 1)
			mlx_put_pixel(cubes, x, y, find_pixel_colour(relevant_texture, (int)pixel_index - 1));
		if ((int)pixel_index % 4 == 2)
			mlx_put_pixel(cubes, x, y, find_pixel_colour(relevant_texture, (int)pixel_index - 2));
		if ((int)pixel_index % 4 == 3)
			mlx_put_pixel(cubes, x, y, find_pixel_colour(relevant_texture, (int)pixel_index - 3));
		y++;
		i++;
	}
	// printf("x: %i, y: %i\n", x, y);
	// if (y < SCREEN_HEIGHT && x < SCREEN_WIDTH)
		// mlx_put_pixel(cubes, x, y, get_rgba(255, 255, 255, 255));
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

	// fixing how close the player is to the wall -> maybe turn this into a double as a separate variable belonging to player
	player.x_grid = player.x_grid + 0.5;
	player.y_grid = player.y_grid + 0.5;

	x = 0;
	while (x < SCREEN_WIDTH)
	// while (x < 10) // for testing
	{
		ray_info.cube_width[0] = x;
		// determine first cube hit
		ray_info.cube_hit = find_cube_hit(ray_info, player, x, &data->scene.map);
		// loop until different cube hit
		while ((find_cube_hit(ray_info, player, x, &data->scene.map).x) == ray_info.cube_hit.x && \
(find_cube_hit(ray_info, player, x, &data->scene.map).y) == ray_info.cube_hit.y)
			x++;
		// at the end of this loop, i should have a cube_indices[0] & [1]
		ray_info.cube_width[1] = x - 1;
		x = ray_info.cube_width[0];
		// printf("current cube: x: %f & y: %f, goes from %i until %i\n", cube_hit.x, cube_hit.y, cube_width[0], cube_width[1]);
		while (x <= ray_info.cube_width[1])
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
			// printf("distance: %f, x: %i\n", ray_info.wall_distance, x);
			draw_texture_line(ray_info, data->visuals.cubes, x, data->textures);
			x++;
		}
	}
	mlx_image_to_window(data->visuals.mlx, data->visuals.cubes, 0, 0);
	return (0);
}

/** Opens the textures stored in the paths in the scene struct. */
int	store_textures(t_scene *scene, t_textures *textures)
{
	textures->north_texture = mlx_load_png(scene->texture_north);
	if (!textures->north_texture)
		return (1);
	textures->east_texture = mlx_load_png(scene->texture_east);
	if (!textures->east_texture)
		return (1);
	textures->south_texture = mlx_load_png(scene->texture_south);
	if (!textures->south_texture)
		return (1);
	textures->west_texture = mlx_load_png(scene->texture_west);
	if (!textures->west_texture)
		return (1);
	// make sure to destroy previous textures when one goes wrong
	// ^ unless you only destroy images and not textures; read up on MLX42
	return (0);
}

/* For continuous updates, called by mlx_loop_hook() and updates player 
   movement/rotation based and re-renders the frame. Called every frame at ~60 FPS. */
void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
 	update_player(data);
	display_cubes(data);
}

/** (itan) CHANGE: I refactored this a bit to accept the megastruct and init
    t_data fields that weren't set elsewhere (like visuals and textures).
    Now using mlx_loop_hook() to attach game_loop() for continuous frame updates
	with movement/rotation. */
int	visualisation(t_data *data)
{
	set_up_player(&data->player, data->scene.map);
	print_player_info(data->player); // test only, remove later

	data->visuals.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!data->visuals.mlx)
		return (1);
	data->visuals.background = mlx_new_image(data->visuals.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->visuals.background)
		return (1);
	data->visuals.floor_colour = get_rgba_from_array(data->scene.floor_color);
	data->visuals.ceiling_colour = get_rgba_from_array(data->scene.ceil_color);

	if (store_textures(&data->scene, &data->textures) != 0)
		printf("texture opening error! make more specific!\n");
	if (display_floor_ceiling(&data->visuals) != NO_ERROR)
		return (1);
	display_cubes(data);

	mlx_key_hook(data->visuals.mlx, handle_keys, data);
	mlx_loop_hook(data->visuals.mlx, game_loop, data);
	mlx_loop(data->visuals.mlx);
	mlx_terminate(data->visuals.mlx);
	return (0);
}
