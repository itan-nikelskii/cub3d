/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:06:02 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/22 13:44:56 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* For continuous updates, called by mlx_loop_hook() and updates player 
   movement/rotation based and re-renders the frame. Called every frame at ~60 FPS. 
   (Manon: added deleting the existing image here instead of inside displaying cubes
   so we don't have to check whether it's the first time)*/
void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
 	update_player(data);
	mlx_delete_image(data->visuals.mlx, data->visuals.cubes);
	display_cubes(data);
}

/** Deletes textures in order N, E, S, W. Only deletes the amount that were
 * created.
 */
void	delete_textures(t_textures *textures, int amount)
{
	if (amount >= 1)
		mlx_delete_texture(textures->north_texture);
	if (amount >= 2)
	mlx_delete_texture(textures->east_texture);
	if (amount >= 3)
		mlx_delete_texture(textures->south_texture);
	if (amount == 4)
		mlx_delete_texture(textures->west_texture);
}

/** Clean the map and texture strings, and optionally clean the textures
 * created by MLX42 depending on whether they've been set up.
 */
void	clean_up(t_data *data, bool textures_done)
{
	free_tab(data->scene.map.grid);
	free(data->scene.texture_north);
	free(data->scene.texture_east);
	free(data->scene.texture_south);
	free(data->scene.texture_west);
	if (textures_done)
		delete_textures(&data->textures, 4);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map_path.cub>");
	parse(argv[1], &data.scene);
	data.visuals.cubes = NULL;
	data.visuals.background = NULL;
	data.visuals.mlx = NULL;
	if (initialisation(&data) != NO_ERROR)
		return (1);
	visualisation(&data);
	mlx_key_hook(data.visuals.mlx, handle_keys, &data);
	mlx_loop_hook(data.visuals.mlx, game_loop, &data);
	mlx_loop(data.visuals.mlx);
	clean_up(&data, true);
	mlx_terminate(data.visuals.mlx);
	return (0);
}
