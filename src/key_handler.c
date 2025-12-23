/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:54:58 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/22 19:38:24 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: documentation; maybe other keys? (apart from movement/rotation, those
// are handled in update_player()); update: added mm toggle support
void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->visuals.mlx);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		toggle_minimap(data);
}
