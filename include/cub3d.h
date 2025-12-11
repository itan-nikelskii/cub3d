/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:01:25 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/11 11:31:05 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parser.h"
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// manon function -> to be split / changed
int	visualisation(t_map *map, t_scene *scene);
uint32_t get_rgba_from_array(int arr[3]);
// probably won't need this one anymore if we're doing everything w the array version
// but keep for now just in case
uint32_t get_rgba(int r, int g, int b, int a);

// itan's key handler
void	handle_keys(mlx_key_data_t keydata, void *param);

#endif
