/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:06:02 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/22 10:40:15 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* For continuous updates, called by mlx_loop_hook() and updates player 
   movement/rotation based and re-renders the frame. Called every frame at ~60 FPS. */
void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
 	update_player(data);
	display_cubes(data);
}

/** Clean everything (map, texture strings, mlx textures) at the end of a
 * successful game. */
void	clean_up(t_data *data)
{
	free_tab(data->scene.map.grid);
	free(data->scene.texture_north);
	free(data->scene.texture_east);
	free(data->scene.texture_south);
	free(data->scene.texture_west);
	mlx_delete_texture(data->textures.east_texture);
	mlx_delete_texture(data->textures.north_texture);
	mlx_delete_texture(data->textures.west_texture);
	mlx_delete_texture(data->textures.south_texture);
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
	initialisation(&data);
	visualisation(&data);
	mlx_key_hook(data.visuals.mlx, handle_keys, &data);
	mlx_loop_hook(data.visuals.mlx, game_loop, &data);
	mlx_loop(data.visuals.mlx);
	mlx_terminate(data.visuals.mlx);
	clean_up(&data);
	return (0);
}
