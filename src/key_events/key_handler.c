/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:54:58 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/09 15:21:28 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Handle key press events for Escape (exit) and M (toggle minimap) keys. */
void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->visuals.mlx);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		toggle_minimap(data);
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
