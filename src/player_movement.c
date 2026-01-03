/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:30:00 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/03 18:04:40 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/* Check if the new position would collide with a wall. Return true if all good,
   false if collision detected.
   - data: game data containing map and player state;
   - new_x: candidate x position in grid coordinates;
   - new_y: candidate y position in grid coordinates. */
bool	check_wall_collision(t_data *data, double new_x, double new_y)
{
	char	tile;
	int		x_direction;
	int		y_direction;

	if (data->player.x_grid - new_x > 0)
		x_direction = -1;
	else if (data->player.x_grid == new_x)
		x_direction = 0;
	else
		x_direction = 1;
	if (data->player.y_grid - new_y > 0)
		y_direction = -1;
	else if (data->player.y_grid == new_y)
		y_direction = 0;
	else
		y_direction = 1;
	if (new_x < 0 || new_y < 0 || new_y >= data->scene.map.height - 1
		|| new_x >= data->scene.map.width - 1)
		return (false);
	tile = data->scene.map.grid[(int)(new_y + y_direction * COLLISION_BUFFER)] \
		[(int)(new_x + x_direction * COLLISION_BUFFER)];
	if (tile == '1' || ft_isspace(tile))
		return (false);
	return (true);
}

/* Try to move along just the x-axis; if blocked, try the y-axis. */
static void	apply_wall_slide(t_data *data, double move_x, double move_y)
{
	double	new_pos;

	new_pos = data->player.x_grid + move_x * MOVE_SPEED;
	if (check_wall_collision(data, new_pos, data->player.y_grid))
	{
		data->player.x_grid = new_pos;
		return ;
	}
	new_pos = data->player.y_grid + move_y * MOVE_SPEED;
	if (check_wall_collision(data, data->player.x_grid, new_pos))
		data->player.y_grid = new_pos;
}

/**
 * Move the player in the given direction with wall sliding (if the full 
   movement would collide, try moving along each axis independently.
 * - data: game data containing map and player state
 * - move_x: x component of movement direction (use with MOVE_SPEED)
 * - move_y: y component of movement direction (use with MOVE_SPEED)
 */
void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x_grid + move_x * MOVE_SPEED;
	new_y = data->player.y_grid + move_y * MOVE_SPEED;
	if (check_wall_collision(data, new_x, new_y))
	{
		data->player.x_grid = new_x;
		data->player.y_grid = new_y;
	}
	else
		apply_wall_slide(data, move_x, move_y);
}

/* Rotate the player view direction and camera plane vectors. Positive angle 
   = counterclockwise (left), negative = clockwise (right).
   - data: game data containing player direction vectors
   - angle: rotation amount in radians (positive = left, negative = right). */
void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.facing.x;
	data->player.facing.x = old_dir_x * cos(angle) - data->player.facing.y
		* sin(angle);
	data->player.facing.y = old_dir_x * sin(angle) + data->player.facing.y
		* cos(angle);
	old_plane_x = data->player.camera_plane.x;
	data->player.camera_plane.x = old_plane_x * cos(angle)
		- data->player.camera_plane.y * sin(angle);
	data->player.camera_plane.y = old_plane_x * sin(angle)
		+ data->player.camera_plane.y * cos(angle);
}

/* Update player state based on current key presses. */
void	update_player(t_data *data)
{
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_W))
		move_player(data, data->player.facing.x, data->player.facing.y);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_S))
		move_player(data, -data->player.facing.x, -data->player.facing.y);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_A))
		move_player(data, data->player.facing.y, -data->player.facing.x);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_D))
		move_player(data, -data->player.facing.y, data->player.facing.x);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_LEFT))
		rotate_player(data, -ROTATE_SPEED);
	if (mlx_is_key_down(data->visuals.mlx, MLX_KEY_RIGHT))
		rotate_player(data, ROTATE_SPEED);
}
