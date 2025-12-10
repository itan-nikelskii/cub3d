/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:01:25 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/10 15:57:14 by mgroos           ###   ########.fr       */
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

#endif
