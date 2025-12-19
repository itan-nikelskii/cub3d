/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:38:14 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/19 11:08:51 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/** In the player struct, stores the x and y coordinates for the direction
 * the player is facing at the start.
 */
static void	set_player_facing(t_player *player, int direction)
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

/** Function to store start info in player struct. The direction the player is
 * facing and the camera plane direction (all in x and y) are stored depending
 * on the cardinal direction given in the map.
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
		player->camera_plane.x = 0.5;
		player->camera_plane.y = 0;
	}
	if (map.player_dir == 'E')
	{
		set_player_facing(player, EAST);
		player->camera_plane.x = 0;
		player->camera_plane.y = 0.5;
	}
	if (map.player_dir == 'S')
	{
		set_player_facing(player, SOUTH);
		player->camera_plane.x = -0.5;
		player->camera_plane.y = 0;
	}
	if (map.player_dir == 'W')
	{
		set_player_facing(player, WEST);
		player->camera_plane.x = 0;
		player->camera_plane.y = -0.5;
	}
}
