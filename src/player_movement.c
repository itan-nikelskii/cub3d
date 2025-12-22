/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:30:00 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/22 15:02:38 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// TODO: maybe fix faster diagonal movement later? not urgent but could be nice

// TODO: put these into master header
#define MOVE_SPEED 0.05
#define ROTATE_SPEED 0.025
#define COLLISION_BUFFER 0.2 // to prevent clipping, can fiddle with it a bit more

// /* Check if the new position would collide with a wall. Return true if all good,
//    false if collision detected.
//    - data: game data containing map and player state;
//    - new_x: candidate x position in grid coordinates;
//    - new_y: candidate y position in grid coordinates. */
// bool	check_wall_collision(t_data *data, double new_x, double new_y)
// {
// 	int		grid_x;
// 	int		grid_y;
// 	char	tile;

// 	// check the grid square at the new position with collision buffer
// 	grid_x = (int)(new_x);
// 	grid_y = (int)(new_y);
// 	// check bounds first; if out of bounds, it's a collision 
// 	if (grid_x < 0 || grid_y < 0 || 
// 		grid_y >= data->scene.map.height || 
// 		grid_x >= data->scene.map.width)
// 		return (false);
// 	// get the map tile at this position
// 	tile = data->scene.map.grid[grid_y][grid_x];
// 	if (tile == '1')
// 	{
// 		return (false); // since 1 = wall
// 	}

// 	return (true);
// }

/* Check if the new position would collide with a wall. Return true if all good,
   false if collision detected.
   - data: game data containing map and player state;
   - new_x: candidate x position in grid coordinates;
   - new_y: candidate y position in grid coordinates. */
bool	check_wall_collision(t_data *data, double new_x, double new_y)
{
	double		grid_x;
	double	grid_y;
	char	tile;

	// check the grid square at the new position with collision buffer
	grid_x = (new_x);
	grid_y = (new_y);
	// check bounds first; if out of bounds, it's a collision 
	if (grid_x < 0.25 || grid_y < 0.25 || 
		grid_y >= data->scene.map.height - 0.25 || 
		grid_x >= data->scene.map.width - 0.25)
		return (false);
	// get the map tile at this position
	tile = data->scene.map.grid[(int)grid_y][(int)grid_x];
	if (tile == '1')
	{
		return (false); // since 1 = wall
	}

	return (true);
}

// /* TODO: this handles position updates for both grid coordinates (main thing for
//    raycasting) AND pixel coordinates for potential minimap/debug display. If no
//    minimap, we can ignore or delete pixel coords later */
// /**
//  * Moves the player in the given direction with wall sliding (if the full 
//    movement would collide, try moving along each axis independently.
//  * - data: game data containing map and player state
//  * - move_x: x component of movement direction (use with MOVE_SPEED)
//  * - move_y: y component of movement direction (use with MOVE_SPEED)
//  */
// void	move_player(t_data *data, double move_x, double move_y)
// {
// 	double	new_x;
// 	double	new_y;
// 	double	slide_x;
// 	double	slide_y;

// 	// calculate new position based on movement direction and speed
// 	new_x = data->player.x_grid + move_x * MOVE_SPEED;
// 	new_y = data->player.y_grid + move_y * MOVE_SPEED;

// 	// try full movement first
// 	if (check_wall_collision(data, new_x, new_y))
// 	{
// 		data->player.x_grid = new_x;
// 		data->player.y_grid = new_y;
// 	}
// 	else
// 	{
// 		// wall collision -> try sliding along walls by moving each axis separately
// 		slide_x = data->player.x_grid + move_x * MOVE_SPEED;
// 		slide_y = data->player.y_grid;
// 		if (check_wall_collision(data, slide_x, slide_y))
// 		{
// 			data->player.x_grid = slide_x;
// 		}
// 		else
// 		{
// 			// x-axis blocked, try just y
// 			slide_x = data->player.x_grid;
// 			slide_y = data->player.y_grid + move_y * MOVE_SPEED;
// 			if (check_wall_collision(data, slide_x, slide_y))
// 				data->player.y_grid = slide_y;
// 		}
// 	}
// 	// update pixel coords too just in case
// 	data->player.x_pixels = (int)(data->player.x_grid * 64 + 32);
// 	data->player.y_pixels = (int)(data->player.y_grid * 64 + 32);
// }


/* TODO: this handles position updates for both grid coordinates (main thing for
   raycasting) AND pixel coordinates for potential minimap/debug display. If no
   minimap, we can ignore or delete pixel coords later */
/**
 * Moves the player in the given direction with wall sliding (if the full 
   movement would collide, try moving along each axis independently.
 * - data: game data containing map and player state
 * - move_x: x component of movement direction (use with MOVE_SPEED)
 * - move_y: y component of movement direction (use with MOVE_SPEED)
 */
void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	slide_x;
	double	slide_y;

	// calculate new position based on movement direction and speed
	new_x = data->player.x_grid + move_x * MOVE_SPEED;
	new_y = data->player.y_grid + move_y * MOVE_SPEED;

	// try full movement first
	if (check_wall_collision(data, new_x, new_y))
	{
		data->player.x_grid = new_x;
		data->player.y_grid = new_y;
	}
	else
	{
		// wall collision -> try sliding along walls by moving each axis separately
		slide_x = data->player.x_grid + move_x * MOVE_SPEED;
		slide_y = data->player.y_grid;
		if (check_wall_collision(data, slide_x, slide_y))
		{
			data->player.x_grid = slide_x;
		}
		else
		{
			// x-axis blocked, try just y
			slide_x = data->player.x_grid;
			slide_y = data->player.y_grid + move_y * MOVE_SPEED;
			if (check_wall_collision(data, slide_x, slide_y))
				data->player.y_grid = slide_y;
		}
	}
	// update pixel coords too just in case
	// printf("actual y grid inside move_player:\t%f\n", data->player.y_grid);
	data->player.x_pixels = (int)(data->player.x_grid * TILE_SIZE);
	data->player.y_pixels = (int)(data->player.y_grid * TILE_SIZE);
	// data->player.x_pixels = (int)(data->player.x_grid * TILE_SIZE + TILE_SIZE / 2);
	// data->player.y_pixels = (int)(data->player.y_grid * TILE_SIZE + TILE_SIZE / 2);
	// printf("actual y pixels inside move_player:\t%d\n", data->player.y_pixels);
}

/* Rotate the player view direction and camera plane vectors. Positive angle 
   = counterclockwise (left), negative = clockwise (right).
   - data: game data containing player direction vectors
   - angle: rotation amount in radians (positive = left, negative = right). */
void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	// rotation matrix applied to facing direction vector (playing with these results in some cool trippy effects! try reversing signs, sin/cos, etc if interested)
	old_dir_x = data->player.facing.x;
	data->player.facing.x = old_dir_x * cos(angle) - data->player.facing.y * sin(angle); 
	data->player.facing.y = old_dir_x * sin(angle) + data->player.facing.y * cos(angle);
	// rotation matrix applied to camera plane vector
	old_plane_x = data->player.camera_plane.x;
	data->player.camera_plane.x = old_plane_x * cos(angle) - data->player.camera_plane.y * sin(angle);
	data->player.camera_plane.y = old_plane_x * sin(angle) + data->player.camera_plane.y * cos(angle);
}

/* Update player state based on current key presses. */
void	update_player(t_data *data)
{
	// movement with WASD
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_W))
		move_player(data, data->player.facing.x, data->player.facing.y);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_S))
		move_player(data, -data->player.facing.x, -data->player.facing.y);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_A))
		move_player(data, data->player.facing.y, -data->player.facing.x);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_D))
		move_player(data, -data->player.facing.y, data->player.facing.x);
	// rotation with arrows
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_LEFT))
		rotate_player(data, -ROTATE_SPEED);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_RIGHT))
		rotate_player(data, ROTATE_SPEED);
}
