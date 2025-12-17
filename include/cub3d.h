/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:01:25 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/15 17:33:37 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parser.h"
# include "visualisation.h"
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>

/* - scene: parsed map, textures, and colors from .cub file
   - player: player position, direction, and camera plane vectors;
   - visuals: MLX window, background image, and color values;
   - textures: png texture pointers for all 4 walls. */
typedef struct s_data
{
	t_scene		scene;
	t_player	player;
	t_visuals	visuals;
	t_textures	textures;
}	t_data;

int	visualisation(t_data *data);
uint32_t get_rgba_from_array(int arr[3]);
// probably won't need this one anymore if we're doing everything w the array version
// but keep for now just in case
uint32_t get_rgba(int r, int g, int b, int a);

// itan's input and key handling; TODO: some of these can def be static
void	handle_keys(mlx_key_data_t keydata, void *param);
void	update_player(t_data *data);
void	move_player(t_data *data, double move_x, double move_y);
void	rotate_player(t_data *data, double angle);
bool	check_wall_collision(t_data *data, double new_x, double new_y);

#endif
