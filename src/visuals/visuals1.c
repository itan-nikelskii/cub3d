/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:33:39 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/17 12:30:50 by mgroos           ###   ########.fr       */
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

/** In the player struct, stores the x and y coordinates for the direction
 * the player is facing at the start.
 */
void	set_player_facing(t_player *player, int direction)
{
	if (direction == NORTH)
	{
		player->facing.x = 0;
		player->facing.y = -1;
	}
	if (direction == EAST)
	{
		player->facing.x = 1;
		player->facing.y = 0;
	}
	if (direction == SOUTH)
	{
		player->facing.x = 0;
		player->facing.y = 1;
	}
	if (direction == WEST)
	{
		player->facing.x = -1;
		player->facing.y = 0;	
	}
}

/** Function to store start info in player struct -> if we have a mega-struct, 
 * might be good to store player in there.
 */
void	set_up_player(t_player *player, t_map map)
{
	player->x_pixels = map.p_x * TILE_SIZE + TILE_SIZE / 2;
	player->y_pixels = map.p_y * TILE_SIZE + TILE_SIZE / 2;
	player->x_grid = map.p_x;
	player->y_grid = map.p_y;
	if (map.player_dir == 'N')
	{
		set_player_facing(player, NORTH);
		player->camera_plane.x = 1; // i think ? they do 0.66 in example
		player->camera_plane.y = 0;
	}
	if (map.player_dir == 'E')
	{
		set_player_facing(player, EAST);
		player->camera_plane.x = 0;
		player->camera_plane.y = 1;
	}
	if (map.player_dir == 'S')
	{
		set_player_facing(player, SOUTH);
		player->camera_plane.x = 1;
		player->camera_plane.y = 0;
	}
	if (map.player_dir == 'W')
	{
		set_player_facing(player, WEST);
		player->camera_plane.x = 0;
		player->camera_plane.y = 1;
	}
}

/** Draw a vertical line based on the distance from the wall. */
void	draw_texture_line(double wall_distance, mlx_image_t *cubes, int x,
	int side, t_textures textures, int cube_width[2])
{
	int				highest_point;
	int				lowest_point;
	float			line_height;
	int			 	y;
	mlx_texture_t 	*relevant_texture;
	float			pixel_index;
	int				i;

	line_height = (float)fabs(SCREEN_HEIGHT / wall_distance);
	highest_point = (int)line_height / 2 + SCREEN_HEIGHT / 2;
	lowest_point = -(int)line_height / 2 + SCREEN_HEIGHT / 2;
	// could pass the texture instead of the side from prev function to save some lines
	if (side == NORTH)
		relevant_texture = textures.north_texture;
	if (side == EAST)
		relevant_texture = textures.east_texture;
	if (side == SOUTH)
		relevant_texture = textures.south_texture;
	if (side == WEST)
		relevant_texture = textures.west_texture;

	y = lowest_point;
	i = 0;

	// real
	// printf("going into the loop now\n");
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
			// printf("y: %i", y);
			i++;
			y++;
			continue ;
		}

		pixel_index = 4 * ((int)(x - cube_width[0]) * \
(relevant_texture->width) / (cube_width[1] - cube_width[0] + 1) + \
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

/** At the start of each loop to determine the pixels on the vertical line of 
 * the screen to draw, set ray_info to contain starting location, 
 * camera_coordinate, and x and y direction.
 */
void	set_ray_starting_point(t_ray *ray_info, t_player player, int x)
{
		// reset ray start point	
		ray_info->map_square[X] = player.x_grid - 0.5;
		ray_info->map_square[Y] = player.y_grid - 0.5;		

		// which vertical line are we watching
		ray_info->camera_coordinate = 2 * x / (double)SCREEN_WIDTH - 1;
		// direction of the ray in x and y
		ray_info->ray_direction.x = player.facing.x + player.camera_plane.x \
* ray_info->camera_coordinate;
		ray_info->ray_direction.y = player.facing.y + player.camera_plane.y \
* ray_info->camera_coordinate;	

}

/** Set delta distance X and Y in the ray struct. */
void	set_delta_distances(t_ray *ray_info)
{
	if (ray_info->ray_direction.x != 0)
	{
		ray_info->delta_distance[X] = sqrt(1 + (ray_info->ray_direction.y * \
ray_info->ray_direction.y) / (ray_info->ray_direction.x * ray_info->ray_direction.x));
	}
	else
		ray_info->delta_distance[X] = INT_MAX; // can be done more elegantly
	if (ray_info->ray_direction.y != 0)
	{
		ray_info->delta_distance[Y] = sqrt(1 + (ray_info->ray_direction.x * \
ray_info->ray_direction.x) /(ray_info->ray_direction.y * ray_info->ray_direction.y));
	}
	else
		ray_info->delta_distance[Y] = INT_MAX; // can be done more elegantly
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

t_vector find_cube_hit(t_ray ray_info, t_player player, int x, t_map *map)
{
	t_vector	cube_hit;

	set_ray_starting_point(&ray_info, player, x);
	set_delta_distances(&ray_info);
	set_ray_info(&ray_info, player);
	int	wall_hit;

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

	cube_hit.x = (double)ray_info.map_square[X]; // should be int
	cube_hit.y = (double)ray_info.map_square[Y];// should be int

	return (cube_hit);
}


/** Function to set up the vertical rays. */
int	display_cubes(t_player player, t_map *map, mlx_t *mlx, t_textures textures)
{
	int 		x; // index for each vertical stripe
	t_ray		ray_info;
	int			side; // side that got hit: NORTH / SOUTH / EAST / WEST
	mlx_image_t *cubes; // image we will write all the vertical lines into
	t_vector	cube_hit; // make a variant of t_vector that has ints instead
	int			cube_width[2];

	cubes = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cubes)
		return (printf("new image err\n"), -1);

	// fixing how close the player is to the wall
	player.x_grid = player.x_grid + 0.5;
	player.y_grid = player.y_grid + 0.5;

	x = 0;


	while (x < SCREEN_WIDTH)
	// while (x < 10) // for testing
	{
		cube_width[0] = x;
		// determine first cube hit
		cube_hit = find_cube_hit(ray_info, player, x, map);
		// loop until different cube hit
		while ((find_cube_hit(ray_info, player, x, map).x) == cube_hit.x && \
(find_cube_hit(ray_info, player, x, map).y) == cube_hit.y)
			x++;
		// at the end of this loop, i should have a cube_indices[0] & [1]
		cube_width[1] = x - 1;
		x = cube_width[0];
		printf("current cube: x: %f & y: %f, goes from %i until %i\n", cube_hit.x, cube_hit.y, cube_width[0], cube_width[1]);
		while (x <= cube_width[1])
		{
			set_ray_starting_point(&ray_info, player, x);
			// determine length of ray from one side to the next
			set_delta_distances(&ray_info);
			// for this next part it's important both player pixel location & player
			// grid coordinates are up to date -> handle that in movement function
			set_ray_info(&ray_info, player);
			side = perform_dda(&ray_info, map);
			// calculations for camera: shortest distance from camera plane to wall hit
			// take one step back since you've already hit a wall
			if (side == EAST || side == WEST)
				ray_info.wall_distance = (ray_info.map_square[X] - player.x_grid + (1 - ray_info.take_step[X]) / 2) / ray_info.ray_direction.x;
			else
				ray_info.wall_distance = (ray_info.map_square[Y] - player.y_grid + (1 - ray_info.take_step[Y]) / 2) / ray_info.ray_direction.y;
			// printf("distance: %f, x: %i\n", ray_info.wall_distance, x);
			draw_texture_line(ray_info.wall_distance, cubes, x, side, textures, cube_width);
			x++;
		}
	}
	mlx_image_to_window(mlx, cubes, 0, 0);
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

int	visualisation(t_map *map, t_scene *scene)
{
	t_visuals 	visuals;
	t_textures	textures;

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
	if (store_textures(scene, &textures) != 0)
		printf("texture opening error! make more specific!\n");
	display_floor_ceiling(&visuals);
	display_cubes(visuals.player, map, visuals.mlx, textures); // also contains the calculations

	// run mlx loop until quit
	mlx_key_hook(visuals.mlx, handle_keys, visuals.mlx); // key_hook, loop, and terminate should ideally be factored out of visuals into main later
	mlx_loop(visuals.mlx);
    mlx_terminate(visuals.mlx);
	return (0);
}
