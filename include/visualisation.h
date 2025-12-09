#ifndef VISUALISATION_H
# define VISUALISATION_H

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
	int			x_grid;
	int			y_grid;
	t_vector	*facing;
	t_vector	*camera_plane;
}	t_player;

# endif