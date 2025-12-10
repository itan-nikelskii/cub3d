/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:06:02 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/10 10:39:49 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map_path.cub>");
	parse(argv[1], &scene);
	visualisation_section(&scene.map, &scene);
	return (0);
}
