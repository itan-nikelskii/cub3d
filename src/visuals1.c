/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:33:39 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/08 17:05:09 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "visualisation.h"
#include "cub3d.h"

# define TILE_SIZE 64
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 1024

/** Make a single unsgined int with the colour out of the rgba values
 * (a = alpha channel for transparency, set to 255 when not using) */
uint32_t get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

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
	player->x_coord = map.p_x * TILE_SIZE + TILE_SIZE / 2;
	player->y_coord = map.p_y * TILE_SIZE + TILE_SIZE / 2;
	player->facing = ft_calloc(1, sizeof(t_vector));
	player->camera_plane = ft_calloc(1, sizeof(t_vector));
	if (!player->facing)
		return (printf("calloc fail\n"), 1);
	// need to include camera plane for all others as well, but first want to test
	// need NULL check camera plane if we do them here
	if (map.player_dir == 'N')
	{
		player->facing->x = 0;
		player->facing->y = -1;
		player->camera_plane->x = 1; // i think ?
		player->camera_plane->y = 0;
	}
	if (map.player_dir == 'E')
	{
		player->facing->x = 1;
		player->facing->y = 0;
	}
	if (map.player_dir == 'S')
	{
		player->facing->x = 0;
		player->facing->y = 1;
	}
	if (map.player_dir == 'W')
	{
		player->facing->x = -1;
		player->facing->y = 0;
	}
	return (0);
}

// testing only !
void print_player_info(t_player player)
{
	printf("player struct location x=%i & y=%i. direction: x=%f & y=%f\n", 
	player.x_coord, player.y_coord, player.facing->x, player.facing->y);
}

/** Function to set up the vertical rays. */
int	calculate_rays(t_player player)
{
	int x; // index for each vertical stripe
	t_vector *ray_direction; // check if maybe we want to pass this to the function
	double	camera_coordinate;
	// (void)map;

	// error handling
	ray_direction = ft_calloc(1, sizeof(t_vector));

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_coordinate = 2 * x / SCREEN_WIDTH - 1;
		ray_direction->x = player.facing->x + player.camera_plane->x * camera_coordinate;
		ray_direction->y = player.facing->y + player.camera_plane->y * camera_coordinate;
	
		// DO MORE
		x++;
	}

	return (0);
}

// int main(void)
int	visualisation_section(t_map *map)
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

	// these will be coming from parsing struct
	int floor_r = 183;
	int floor_g = 234;
	int floor_b = 194;

	int ceiling_r = 200;
	int ceiling_g = 255;
	int ceiling_b = 255;

	// turn 3 rgb values into one colour -> ideally this is done earlier so the
	// struct only needs to contain 2 unsigned ints instead of 6 ints.
	uint32_t floor_colour = get_rgba(floor_r, floor_g, floor_b, 255);
	uint32_t ceiling_colour = get_rgba(ceiling_r, ceiling_g, ceiling_b, 255);

	calculate_rays(*player);

	// set pixel colours
	display_floor_ceiling(mlx, background, floor_colour, ceiling_colour);

	// run mlx loop until quit
	// key hook goes here
	mlx_loop(mlx);
    mlx_terminate(mlx);

	return (0);
}
