/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:06:02 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/15 17:08:08 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map_path.cub>");
	parse(argv[1], &data.scene);

	// init image pointers to null
	data.visuals.cubes = NULL;
	data.visuals.background = NULL;
	data.visuals.mlx = NULL;

	visualisation(&data);
	free_tab(data.scene.map.grid);
	return (0);
}
