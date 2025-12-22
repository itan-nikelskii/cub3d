/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:38:14 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/22 13:45:38 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "visualisation.h"

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
	player->x_grid = map.p_x + 0.5;
	player->y_grid = map.p_y + 0.5;
	if (map.player_dir == 'N')
	{
		set_player_facing(player, NORTH);
		player->camera_plane.x = 0.5 * SCREEN_WIDTH / SCREEN_HEIGHT;
		player->camera_plane.y = 0;
	}
	if (map.player_dir == 'E')
	{
		set_player_facing(player, EAST);
		player->camera_plane.x = 0;
		player->camera_plane.y = 0.5 * SCREEN_WIDTH / SCREEN_HEIGHT;
	}
	if (map.player_dir == 'S')
	{
		set_player_facing(player, SOUTH);
		player->camera_plane.x = -0.5 * SCREEN_WIDTH / SCREEN_HEIGHT;
		player->camera_plane.y = 0;
	}
	if (map.player_dir == 'W')
	{
		set_player_facing(player, WEST);
		player->camera_plane.x = 0;
		player->camera_plane.y = -0.5 * SCREEN_WIDTH / SCREEN_HEIGHT;
	}
}

/** Opens the textures stored in the paths in the scene struct. */
int	store_textures(t_scene *scene, t_textures *textures)
{
	textures->north_texture = mlx_load_png(scene->texture_north);
	if (!textures->north_texture)
		return (printf("North texture failed to load"), MLX_FAIL);
	textures->east_texture = mlx_load_png(scene->texture_east);
	if (!textures->east_texture)
	{
		delete_textures(textures, 1);
		return (printf("East texture failed to load"), MLX_FAIL);
	}
	textures->south_texture = mlx_load_png(scene->texture_south);
	if (!textures->south_texture)
	{
		delete_textures(textures, 2);
		return (printf("South texture failed to load"), MLX_FAIL);
	}
	textures->west_texture = mlx_load_png(scene->texture_west);
	if (!textures->west_texture)
	{
		delete_textures(textures, 3);
		return (printf("West texture failed to load"), MLX_FAIL);
	}
	return (NO_ERROR);
}

/** Set up the data struct after parsing: fill in player info, initialise MLX
 * screen, store the background colours and the textures.
 */
int	initialisation(t_data *data)
{
	set_up_player(&data->player, data->scene.map);
	// print_player_info(data->player); // test only, remove later
	data->visuals.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!data->visuals.mlx)
	{
		clean_up(data, false);
		error_exit("MLX: failed to initialise screen.");
	}
	data->visuals.floor_colour = get_rgba_from_array(data->scene.floor_color);
	data->visuals.ceiling_colour = get_rgba_from_array(data->scene.ceil_color);
	if (store_textures(&data->scene, &data->textures) != 0)
	{
		clean_up(data, false);
		mlx_terminate(data->visuals.mlx);
		return (MLX_FAIL);
	}
	return (NO_ERROR);
}
