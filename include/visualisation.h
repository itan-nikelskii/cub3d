#ifndef VISUALISATION_H
# define VISUALISATION_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_vector
{
	double x;
	double y;
}	t_vector;

typedef struct s_coordinates
{
	int x;
	int y;
}	t_coordinates;

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

typedef struct s_ray
{
	double		camera_coordinate;
	t_vector	ray_direction;
	// grid square that the ray is in
	double		map_square[2];
	// length of ray from current position to next x or y side
	t_vector	side_distance;
	// length of ray from one x or y side to next x or y side
	double		delta_distance[2];
	// direction to go, either +1 or -1
	int 		take_step[2];
	// distance between camera plane & wall
	double		 wall_distance;

}	t_ray;

// could also put this struct or all 4 of these items inside of the scene struct!
// probably change the names of the textures in scene struct so theyre "north_path", etc
typedef struct s_textures
{
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
}	t_textures;

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

int		find_pixel_colour(mlx_texture_t *texture, int i);
void	set_ray_starting_point(t_ray *ray_info, t_player player, int x);
void	set_delta_distances(t_ray *ray_info);
void	set_ray_info(t_ray *ray, t_player player);

# endif