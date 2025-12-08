#ifndef VISUALISATION_H
# define VISUALISATION_H

typedef struct s_vector
{
	double x;
	double y;
}	t_vector;

typedef struct s_player
{
	int			x_coord;
	int			y_coord;
	t_vector	*facing;
	t_vector	*camera_plane;
}	t_player;

# endif