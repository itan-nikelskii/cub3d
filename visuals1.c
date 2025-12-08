// file to start testing some visualisation stuff

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"

/** Make a single int with the colour out of the rgba values (a = alpha channel
 * for transparancy) */
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

/** Trying to make a version of get_rgba without a, doesnt seem to work. */
int get_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

// memcpy is not allowed !!!!
int main(void)
{
	mlx_t *mlx = mlx_init(1000, 1000, "cub3D", true);
	if (!mlx)
		return (1);
	mlx_image_t *img = mlx_new_image(mlx, 1000, 1000);

	// for some reason floor colour is yellow instead of pink?
	int floor_r = 255;
	int floor_g = 200;
	int floor_b = 255;
	// for some reason the ceiling colour stays grey instead of blue?
	int ceiling_r = 200;
	int ceiling_g = 255;
	int ceiling_b = 255;

	int floor_colour = get_rgba(floor_r, floor_g, floor_b, 255);
	printf("calc floor colour = %i\n", floor_colour);
	int ceiling_colour = get_rgba(ceiling_r, ceiling_g, ceiling_b, 255);
	printf("calc ceiling colour = %i\n", ceiling_colour);

	unsigned long j = 0;
	while (j < (img->width * img->height / 2))
	{
		memcpy(img->pixels + j * sizeof(int), &ceiling_colour, sizeof(ceiling_colour));
		j++;
	}
	while (j < (img->width * img->height))
	{
		memcpy(img->pixels + j * sizeof(int), &floor_colour, sizeof(floor_colour));
		j++;
	}

	mlx_image_to_window(mlx, img, 0, 0);

	// run mlx loop until quit
	mlx_loop(mlx);
    mlx_terminate(mlx);
}