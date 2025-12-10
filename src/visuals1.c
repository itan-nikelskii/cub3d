/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:33:39 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/10 15:12:27 by mgroos           ###   ########.fr       */
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

/** Uses put_pixel to colour the top half of the image to ceiling colours
 * and the bottom half to floor colours.
 */
void	display_floor_ceiling(mlx_t *mlx, mlx_image_t *img, uint32_t floor_colour,
	uint32_t ceiling_colour) // instead of floor & ceiling colour, can pass mega-struct
{
	unsigned int x = 0;
	unsigned int y = 0;

	while (y < img->height / 2)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, ceiling_colour);
			x++;
		}
		y++;
	}
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, floor_colour);
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	// error handling? could give a return val.
	// might have to split this into two functions if we're displaying floor AFTER walls
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

// testing only !
void print_player_info(t_player player)
{
	printf("player struct location x=%i & y=%i. direction: x=%f & y=%f\n", 
	player.x_pixels, player.y_pixels, player.facing.x, player.facing.y);
}

/** Draw a vertical line based on the distance from the wall. */
void	draw_line(double perpWallDist, mlx_image_t *cubes, int x, int side)
{
	// heighest and lowest point
	int	draw_highest;
	int draw_lowest;
	// height of line to draw
	int line_height;
	int y;
	uint32_t wall_colour;

	// (void)x;
	// (void)cubes;

	// printf("perpwalldist: %f\n", perpWallDist);
	line_height = (int)fabs(SCREEN_HEIGHT / perpWallDist);
	if (line_height < 0)
		line_height = line_height * -1;
	draw_highest = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_highest < 0)
		draw_highest = 0;
	draw_lowest = -line_height / 2 + SCREEN_HEIGHT / 2;

	if (draw_lowest < 0)
		draw_lowest = 0;

	// here we would probably pick out the texture
	// draw! -> will be replaced with texture
	if (side == 1)
		wall_colour = get_rgba(255, 255, 200, 255);
	else
		wall_colour = get_rgba(255, 204, 255, 255);
	y = draw_highest;
	// printf("putting line of height %i at: %i: high: %i, low: %i\n", line_height, x, draw_highest, draw_lowest);
	// mlx_put_pixel(cubes, x, 10, wall_colour); // < this is fine
	while (y > draw_lowest)
	{
		mlx_put_pixel(cubes, x, y, wall_colour);
		//  core dump error?
		y--;
	}
}

/** Function to set up the vertical rays. */
int	calculate_rays(t_player player, t_map *map, mlx_t *mlx)
{
	int x; // index for each vertical stripe
	// some of these vars could maybe be in some kind of ray struct?
	t_vector ray_direction; // check if maybe we want to pass this to the function
	double	camera_coordinate;
	// length of ray from current posi to next x or y side
	double	sideDistX;
	double	sideDistY;
	// length of ray from one x or y side to next x or y side
	double	deltaDistX; 
	double	deltaDistY;
	// direction to go, either + or -1
	int stepX;
	int stepY;
	// check if a wall has been reached, and which
	int wall_hit;;
	int	side; // 0 is E/W wall, 1 is N/S wall -> REFINE!!!
	// grid square that the ray is in
	double mapX;
	double mapY;
	// distance between camera plane & wall
	double perpWallDist;
	// image we will write all the vertical lines into
	mlx_image_t *cubes = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cubes)
		return (printf("calloc err\n"), -1);

	// trying to fix how close player is to wall
	player.x_grid = player.x_grid + 0.5;
	player.y_grid = player.y_grid + 0.5;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		// reset ray start point	
		mapX = player.x_grid - 0.5;
		mapY = player.y_grid - 0.5;		

		// which vertical line are we watching
		camera_coordinate = 2 * x / (double)SCREEN_WIDTH - 1;
		// direction of the ray in x and y
		ray_direction.x = player.facing.x + player.camera_plane.x * camera_coordinate;
		ray_direction.y = player.facing.y + player.camera_plane.y * camera_coordinate;

		// printf("calc direction x: player face: %f, camera plane: %f, cam coordinate: %f\n", player.facing->x, player.camera_plane->x, camera_coordinate);
		// printf("calc direction y: player face: %f, camera plane: %f, cam coordinate: %f\n", player.facing->y, player.camera_plane->y, camera_coordinate);
		// printf("result ray->x = %f, ray->y = %f\n", ray_direction.x, ray_direction.y);

		
		// determine length of ray from one side to the next (if direction == 0,
		// make really large nbr to avoid dividing by 0 error)
		// printf("ray_direction.x = %f & ->y = %f\n", ray_direction.x, ray_direction.y);
		if (ray_direction.x != 0)
		{
			// deltaDistX = fabs(1 / ray_direction.x);
			deltaDistX = sqrt(1 + (ray_direction.y * ray_direction.y) / \
(ray_direction.x * ray_direction.x));
		}
		else
			deltaDistX = INT_MAX; // can be done more elegantly
		if (ray_direction.y != 0)
		{
			// deltaDistY = fabs(1 / ray_direction.y);
			deltaDistY = sqrt(1 + (ray_direction.x * ray_direction.x) / \
(ray_direction.y * ray_direction.y));
		}
		else
			deltaDistY = INT_MAX; // can be done more elegantly

		// for this next part it's important both player pixel location & player
		// grid coordinates are up to date -> handle that in movement function
		if (ray_direction.x < 0)
		{
			stepX = -1;
			sideDistX = (player.x_grid - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			// why the + 1?
			// sideDistX = (player.x_grid - mapX + 1) * deltaDistX;
			sideDistX = (mapX - player.x_grid + 1.0) * deltaDistX;
		}
		if (ray_direction.y < 0)
		{
			stepY = -1;
			sideDistY = (player.y_grid - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY - player.y_grid + 1) * deltaDistY;
		}
		// DDA time!
		wall_hit = 0;
		while (wall_hit == 0)
		{
			// jump to next square -> either X or Y direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// check hit
			if (map->grid[(int)mapY][(int)mapX] == '1')
				wall_hit = 1;
		}
		// printf("found a wall at x:%i y:%i\n", mapX, mapY);
		// printf("sidedistY is: %f / deltadistY: %f\n", sideDistY, deltaDistY);
		// calculations for camera: shortest distance from camera plane to wall hit
		// take one step back since you've already hit a wall
		if (side == 0)
		{
			// perpWallDist = sideDistX - deltaDistX;
			// printf("side 0: perp wall dist: %f: %f - %f\n", perpWallDist, sideDistX, deltaDistX);
			perpWallDist = (mapX - player.x_grid + (1 - stepX) / 2) / ray_direction.x;
		}
		else
		{
			// perpWallDist = sideDistY - deltaDistY;
			// printf("side 1: perp wall dist: %f: %f - %f\n", perpWallDist, sideDistY, deltaDistY);
			perpWallDist = (mapY - player.y_grid + (1 - stepY) / 2) / ray_direction.y;
		}
		draw_line(perpWallDist, cubes, x, side);
		x++;
	}
	mlx_image_to_window(mlx, cubes, 0, 0);
	return (0);
}

// int main(void)
int	visualisation_section(t_map *map, t_scene *scene)
{
	// window sizes etc to be determined
	mlx_t *mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!mlx)
		return (1);
	mlx_image_t *background = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);

	// set up the player struct
	t_player *player;
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (printf("calloc fail\n"), 1);
	set_up_player(player, *map);

	// print tests for the player (remove !)
	print_player_info(*player);

	// turn 3 rgb values into one colour -> ideally this is done earlier so the
	// struct only needs to contain 2 unsigned ints instead of 6 ints.
	uint32_t floor_colour = get_rgba_from_array(scene->floor_color);
	uint32_t ceiling_colour = get_rgba_from_array(scene->ceil_color);

	// set pixel colours
	display_floor_ceiling(mlx, background, floor_colour, ceiling_colour);

	// test
	calculate_rays(*player, map, mlx);

	// run mlx loop until quit
	// key hook goes here
	mlx_loop(mlx);
    mlx_terminate(mlx);

	return (0);
}
