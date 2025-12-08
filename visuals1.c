// file to start testing some visualisation stuff

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"

/** Make a single unsgined int with the colour out of the rgba values
 * (a = alpha channel for transparancy, set to 255 when not using) */
uint32_t get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

/** Uses put_pixel to colour the top half of the image to ceiling colours
 * and the bottom half to floor colours.
 */
void	display_floor_ceiling(mlx_t *mlx, mlx_image_t *img, uint32_t floor_colour,
	uint32_t ceiling_colour)
{
	unsigned int x = 0;
	unsigned int y = 0;

	while (y < img->height / 2)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, ceiling_colour);
			x++;
		}
		y++;
	}
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, floor_colour);
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	// error handling? could give a return val.
}

int main(void)
{
	mlx_t *mlx = mlx_init(2000, 1000, "cub3D", true);
	if (!mlx)
		return (1);
	mlx_image_t *img = mlx_new_image(mlx, 2000, 1000);

	// these will be coming from parsing struct
	int floor_r = 183;
	int floor_g = 234;
	int floor_b = 194;

	int ceiling_r = 200;
	int ceiling_g = 255;
	int ceiling_b = 255;

	// turn 3 rgb values into one colour -> ideally this is done earlier so the
	// struct only needs to contain 2 unsigned ints instead of 6 ints.
	uint32_t floor_colour = get_rgba(floor_r, floor_g, floor_b, 255);
	uint32_t ceiling_colour = get_rgba(ceiling_r, ceiling_g, ceiling_b, 255);

	// set pixel colours
	display_floor_ceiling(mlx, img, floor_colour, ceiling_colour);

	// run mlx loop until quit
	mlx_loop(mlx);
    mlx_terminate(mlx);
}
