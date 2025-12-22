/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:01:25 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/22 16:20:24 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parser.h"
// # include "visualisation.h"
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>

# define TILE_SIZE 64
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 1024

typedef struct s_vector
{
	double x;
	double y;
}	t_vector;

/** Player coordinates in both pixels and squares, vector for the direction
 * the player is facing in, and vector for the camera plane (perpendicular to
 * player view)
 */
typedef struct s_player
{
	int			x_pixels;
	int			y_pixels;
	double		x_grid;
	double		y_grid;
	t_vector	facing;
	t_vector	camera_plane;
}	t_player;

typedef struct s_visuals_struct
{
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*cubes;
	uint32_t	floor_colour;
	uint32_t	ceiling_colour;

}	t_visuals;

// could also put this struct or all 4 of these items inside of the scene struct!
// probably change the names of the textures in scene struct so theyre "north_path", etc
typedef struct s_textures
{
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
}	t_textures;

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
	unsigned int	time; // for animation
}	t_data;

/** Possible errors to use as return values. */
enum e_errors
{
	NO_ERROR,
	CALLOC_FAIL,
	MLX_FAIL
};

int	visualisation(t_data *data);
uint32_t get_rgba_from_array(int arr[3]);
uint32_t get_rgba(int r, int g, int b, int a);

// itan's input and key handling; TODO: some of these can def be static
void	handle_keys(mlx_key_data_t keydata, void *param);
void	update_player(t_data *data);
void	move_player(t_data *data, double move_x, double move_y);
void	rotate_player(t_data *data, double angle);
bool	check_wall_collision(t_data *data, double new_x, double new_y);

// other
void	game_loop(void *param);
int		display_cubes(t_data *data);
void	delete_textures(t_textures *textures, int amount);
void	clean_up(t_data *data, bool textures_done);

// init
void	set_up_player(t_player *player, t_map map);
int		initialisation(t_data *data);

#endif
