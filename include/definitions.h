/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:48:03 by mgroos            #+#    #+#             */
/*   Updated: 2026/01/08 13:09:03 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# define TILE_SIZE 64
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 1024
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.025
# define COLLISION_BUFFER 0.2
# define MINIMAP_W 256
# define MINIMAP_H 256
# define MM_COLOR_WALL 0xFFFFFFFF
# define MM_COLOR_DOT 0xFF0000FF

# include "../MLX42/include/MLX42/MLX42.h"

/*
- grid: a 2D array representing the map. grid[y][x] = the character at row y,
	column x.
- height: the total number of rows
- width: the length of the longest row (all rows will be padded to this length)
- player_count: to ensure that exactly 1 player exists
- player_dir: 'N', 'S', 'E', or 'W' for starting orientation
- p_y: the y coordinate (row index) where the player starts
- p_x: the x coordinate (column index) where the player starts
*/
typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_count;
	char	player_dir;
	int		p_y;
	int		p_x;
}	t_map;

/*
- map: the map grid and player state
- textures: file paths for the wall textures
- floor_color/ceil_color: int arrays for R,G,B
*/
typedef struct s_scene
{
	t_map	map;
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	char	*texture_bonus;
	int		floor_color[3];
	int		ceil_color[3];
}	t_scene;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

/** Player coordinates in both pixels and squares, vector for the direction
 * the player is facing in, and vector for the camera plane (perpendicular to
 * player view)
 */
typedef struct s_player
{
	double		x_grid;
	double		y_grid;
	t_vector	facing;
	t_vector	camera_plane;
}	t_player;

typedef struct s_visuals
{
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*cubes;
	mlx_image_t	*mm_bg;
	mlx_image_t	*mm_player;
	bool		mm_active;
	double		mm_scale;
	uint32_t	floor_colour;
	uint32_t	ceiling_colour;

}	t_visuals;

typedef struct s_textures
{
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*bonus_texture;
}	t_textures;

/* - scene: parsed map, textures, and colors from .cub file
   - player: player position, direction, and camera plane vectors;
   - visuals: MLX window, background image, and color values;
   - textures: png texture pointers for all 4 walls. */
typedef struct s_data
{
	t_scene			scene;
	t_player		player;
	t_visuals		visuals;
	t_textures		textures;
	unsigned int	time;
	bool			bonus_included;
}	t_data;

/** Possible errors to use as return values. */
enum e_errors
{
	NO_ERROR,
	CALLOC_FAIL,
	MLX_FAIL
};

#endif
