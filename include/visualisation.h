#ifndef VISUALISATION_H
# define VISUALISATION_H

#include "cub3d.h"

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
	mlx_image_t *background;
	uint32_t	floor_colour;
	uint32_t	ceiling_colour;

}	t_visuals;

enum e_coordinates
{
	X,
	Y
};

enum e_cardinal_directions
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

# endif