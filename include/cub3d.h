/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:01:25 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/08 13:16:57 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "definitions.h"
# include <stdbool.h>

/* main */
void	game_loop(void *param);
int		visualisation(t_data *data);

/* input & key-handling */
void	handle_keys(mlx_key_data_t keydata, void *param);
void	update_player(t_data *data);
void	move_player(t_data *data, double move_x, double move_y);
void	rotate_player(t_data *data, double angle);
bool	check_wall_collision(t_data *data, double new_x, double new_y);

/* minimap */
void	init_minimap(t_data *data);
void	update_minimap(t_data *data);
void	toggle_minimap(t_data *data);

/* initialisation */
void	set_up_player(t_player *player, t_map map);
int		initialisation(t_data *data);

/* exit & clean-up */
void	error_exit(char *msg);
void	free_tab(char **tab);
void	clean_up(t_data *data, bool textures_done);
void	delete_textures(t_textures *textures, int amount);

#endif
