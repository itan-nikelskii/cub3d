#ifndef VISUALISATION_H
# define VISUALISATION_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "parser.h" // for s_map -> this seems like a waste of splitting headers up, maybe a better way to do this
# include "cub3d.h"

typedef struct s_coordinates
{
	int x;
	int y;
}	t_coordinates;

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
	int				side; // side that got hit: NORTH / SOUTH / EAST / WEST
	// t_coordinates	cube_hit; // coordinates of the cube that was hit
	int				cube_width[2]; // visual start & end coordinates horizontally on the screen
	double		wall_fraction; // horizontal fraction of the wall that was hit by the ray
	// info about the texture line drawn based on the ray
	int			highest_point;
	int			lowest_point;
	float		line_height;

}	t_ray;

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
float	pass_red_index(int pixel_index);
int		perform_dda(t_ray *ray_info, t_map *map);
void	draw_texture_line(t_data *data, t_ray ray, mlx_image_t *cubes, int x);

# endif