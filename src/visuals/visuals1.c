/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:33:39 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/11 11:24:29 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "visualisation.h"
#include "cub3d.h"

# define TILE_SIZE 64
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 1024

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
void	display_floor_ceiling(t_visuals *visuals)
{
	unsigned int x = 0;
	unsigned int y = 0;

	while (y < visuals->background->height / 2)
	{
		x = 0;
		while (x < visuals->background->width)
		{
			mlx_put_pixel(visuals->background, x, y, visuals->ceiling_colour);
			x++;
		}
		y++;
	}
	while (y < visuals->background->height)
	{
		x = 0;
		while (x < visuals->background->width)
		{
			mlx_put_pixel(visuals->background, x, y, visuals->floor_colour);
			x++;
		}
		y++;
	}
	mlx_image_to_window(visuals->mlx, visuals->background, 0, 0);
	// error handling? could give a return val.
}

/** Function to store start info in player struct -> if we have a mega-struct, 
 * might be good to store player in there.
 */
int	set_up_player(t_player *player, t_map map)
{
	player->x_pixels = map.p_x * TILE_SIZE + TILE_SIZE / 2;
	player->y_pixels = map.p_y * TILE_SIZE + TILE_SIZE / 2;
	player->x_grid = map.p_x;
	player->y_grid = map.p_y;
	// need to include camera plane for all others as well, but first want to test
	if (map.player_dir == 'N')
	{
		player->facing.x = 0;
		player->facing.y = -1;
		player->camera_plane.x = 1; // i think ? they do 0.66 in example
		player->camera_plane.y = 0;
	}
	if (map.player_dir == 'E')
	{
		player->facing.x = 1;
		player->facing.y = 0;
		player->camera_plane.x = 0;
		player->camera_plane.y = 1;
	}
	if (map.player_dir == 'S')
	{
		player->facing.x = 0;
		player->facing.y = 1;
		player->camera_plane.x = 1;
		player->camera_plane.y = 0;
	}
	if (map.player_dir == 'W')
	{
		player->facing.x = -1;
		player->facing.y = 0;
		player->camera_plane.x = 0;
		player->camera_plane.y = 1;
	}
	return (0);
}

/** Draw a vertical line based on the distance from the wall. */
void	draw_line(double wall_distance, mlx_image_t *cubes, int x, int side)
{
	int	highest_point;
	int lowest_point;
	int line_height;
	int y;
	// temporary, this will be changed when we have texture instead
	uint32_t wall_colour;

	line_height = (int)fabs(SCREEN_HEIGHT / wall_distance);
	if (line_height < 0)
		line_height = line_height * -1;
	highest_point = line_height / 2 + SCREEN_HEIGHT / 2;
	if (highest_point < 0)
		highest_point = 0;
	lowest_point = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (lowest_point < 0)
		lowest_point = 0;
	// here we would probably pick out the texture
	if (side == NORTH)
		wall_colour = get_rgba(255, 255, 200, 255); // yellow
	if (side == EAST)
		wall_colour = get_rgba(200, 255, 255, 255); // blue
	if (side == SOUTH)
		wall_colour = get_rgba(255, 255, 255, 255); // white
	if (side == WEST)
		wall_colour = get_rgba(255, 200, 255, 255); // pink
	y = highest_point;
	// printf("putting line of height %i at: %i: high: %i, low: %i\n", line_height, x, draw_highest, draw_lowest);
	// mlx_put_pixel(cubes, x, 10, wall_colour); // < this is fine
	while (y > lowest_point)
	{
		mlx_put_pixel(cubes, x, y, wall_colour);
		//  core dump error?
		y--;
	}
}

/** Perform the digital differential analyzer: keep moving small steps until
 * a wall is reached. Then return whether that map is north/south or east/west.
 */
int	perform_dda(t_vector side_distance, double delta_distance[2], double map_square[2],
int take_step[2], t_map *map)
{
	int	wall_hit = 0;
	int	side;// 0 is E/W wall, 1 is N/S wall -> should be refinable to whether it's north or south
	// based on the last step taken, i think?

	while (wall_hit == 0)
		{
			// jump to next square -> either X or Y direction
			if (side_distance.x < side_distance.y)
			{
				side_distance.x += delta_distance[X];
				map_square[X] += take_step[X];
				if (take_step[X] > 0)
					side = EAST;
				else
					side = WEST;
				// side = 0;
			}
			else
			{
				side_distance.y += delta_distance[Y];
				map_square[Y] += take_step[Y];
				if (take_step[Y] > 0)
					side = NORTH;
				else
					side = SOUTH;
				// side = 1;
			}
			// check hit
			if (map->grid[(int)map_square[Y]][(int)map_square[X]] == '1')
				wall_hit = 1;
		}
	return (side);
}

/** Function to set up the vertical rays. */
int	display_cubes(t_player player, t_map *map, mlx_t *mlx)
{
	int x; // index for each vertical stripe
	// some of these vars could maybe be in some kind of ray struct?
	t_vector ray_direction; // check if maybe we want to pass this to the function
	double	camera_coordinate;
	// length of ray from current position to next x or y side
	t_vector	side_distance;
	// length of ray from one x or y side to next x or y side
	double	delta_distance[2];
	// direction to go, either +1 or -1
	int take_step[2];
	// grid square that the ray is in
	double map_square[2];
	// distance between camera plane & wall
	double wall_distance;
	int	side; // side that got hit: NORTH / SOUTH / EAST / WEST
	mlx_image_t *cubes; // image we will write all the vertical lines into
	cubes = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cubes)
		return (printf("calloc err\n"), -1);

	// fixing how close the player is to the wall
	player.x_grid = player.x_grid + 0.5;
	player.y_grid = player.y_grid + 0.5;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		// reset ray start point	
		map_square[X] = player.x_grid - 0.5;
		map_square[Y] = player.y_grid - 0.5;		

		// which vertical line are we watching
		camera_coordinate = 2 * x / (double)SCREEN_WIDTH - 1;
		// direction of the ray in x and y
		ray_direction.x = player.facing.x + player.camera_plane.x * camera_coordinate;
		ray_direction.y = player.facing.y + player.camera_plane.y * camera_coordinate;

		// printf("calc direction x: player face: %f, camera plane: %f, cam coordinate: %f\n", player.facing->x, player.camera_plane->x, camera_coordinate);
		// printf("calc direction y: player face: %f, camera plane: %f, cam coordinate: %f\n", player.facing->y, player.camera_plane->y, camera_coordinate);
		// printf("result ray->x = %f, ray->y = %f\n", ray_direction.x, ray_direction.y);

		// determine length of ray from one side to the next
		// printf("ray_direction.x = %f & ->y = %f\n", ray_direction.x, ray_direction.y);
		if (ray_direction.x != 0)
		{
			// delta_distance[X] = fabs(1 / ray_direction.x);
			delta_distance[X] = sqrt(1 + (ray_direction.y * ray_direction.y) / \
(ray_direction.x * ray_direction.x));
		}
		else
			delta_distance[X] = INT_MAX; // can be done more elegantly
		if (ray_direction.y != 0)
		{
			// delta_distance[Y] = fabs(1 / ray_direction.y);
			delta_distance[Y] = sqrt(1 + (ray_direction.x * ray_direction.x) / \
(ray_direction.y * ray_direction.y));
		}
		else
			delta_distance[Y] = INT_MAX; // can be done more elegantly

		// for this next part it's important both player pixel location & player
		// grid coordinates are up to date -> handle that in movement function
		if (ray_direction.x < 0)
		{
			take_step[X] = -1;
			side_distance.x = (player.x_grid - map_square[X]) * delta_distance[X];
		}
		else
		{
			take_step[X] = 1;
			side_distance.x = (map_square[X] - player.x_grid + 1.0) * delta_distance[X];
		}
		if (ray_direction.y < 0)
		{
			take_step[Y] = -1;
			side_distance.y = (player.y_grid - map_square[Y]) * delta_distance[Y];
		}
		else
		{
			take_step[Y] = 1;
			side_distance.y = (map_square[Y] - player.y_grid + 1) * delta_distance[Y];
		}
		// DDA time!
		side = perform_dda(side_distance, delta_distance, map_square, take_step, map);
		// printf("found a wall at x:%i y:%i\n", map_square[X], map_square[Y]);
		// printf("side_distance.y is: %f / delta_distance[Y]: %f\n", side_distance.y, delta_distance[Y]);
		// calculations for camera: shortest distance from camera plane to wall hit
		// take one step back since you've already hit a wall
		if (side == EAST || side == WEST)
			wall_distance = (map_square[X] - player.x_grid + (1 - take_step[X]) / 2) / ray_direction.x;
		else
			wall_distance = (map_square[Y] - player.y_grid + (1 - take_step[Y]) / 2) / ray_direction.y;
		draw_line(wall_distance, cubes, x, side);
		x++;
	}
	mlx_image_to_window(mlx, cubes, 0, 0);
	return (0);
}

int	visualisation(t_map *map, t_scene *scene)
{
	t_visuals 	visuals;

	set_up_player(&visuals.player, *map);
	print_player_info(visuals.player); // test only, remove
	visuals.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!visuals.mlx)
		return (1);
	visuals.background = mlx_new_image(visuals.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!visuals.background)
		return (1);
	visuals.floor_colour = get_rgba_from_array(scene->floor_color);
	visuals.ceiling_colour = get_rgba_from_array(scene->ceil_color);
	display_floor_ceiling(&visuals);
	display_cubes(visuals.player, map, visuals.mlx); // also contains the calculations

	// run mlx loop until quit
	mlx_key_hook(visuals.mlx, handle_keys, visuals.mlx); // key_hook, loop, and terminate should ideally be factored out of visuals into main later
	mlx_loop(visuals.mlx);
    mlx_terminate(visuals.mlx);
	return (0);
}
