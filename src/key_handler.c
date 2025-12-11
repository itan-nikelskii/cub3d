/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:54:58 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/11 11:42:41 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* - keydata: contains the key code, action (press/release), and modifiers;
   - param: a void pointer to be filled with game data. */
void	handle_keys(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx_instance;	// param is still hella confusing to me, all I know is that we need to cast it to mlx_t to use it here

	mlx_instance = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx_instance);
}
