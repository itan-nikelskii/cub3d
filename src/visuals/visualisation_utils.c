/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:42:28 by mgroos            #+#    #+#             */
/*   Updated: 2026/01/08 13:06:01 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"
#include <stdint.h> // for uint32_t

/** Make a single unsgined int with the colour out of the rgba values
 * (a = alpha channel for transparency, set to 255 when not using) */
uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/** Automatically sets opacity channel to 255, and takes R G B values from
 * int array.
 */
uint32_t	get_rgba_from_array(int rgb[3])
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}

/** Take a pixel array from the MLX texture structs and determine the colour
 * based on the index of the red value in the pixel array.
 * @param pixels uint8_t array of pixels from MLX texture array.
 * @param i Index of the red channel value of the relevant pixel.
 */
int	find_pixel_colour(mlx_texture_t *texture, int i)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	if ((unsigned int)i > (texture->width * texture->height * 4 - 4))
		i = texture->width * texture->height * 4 - 4;
	red = texture->pixels[i];
	green = texture->pixels[i + 1];
	blue = texture->pixels[i + 2];
	alpha = texture->pixels[i + 3];
	return (get_rgba(red, green, blue, alpha));
}

/* Return the R index of the relevant pixel, not G, B or A index. */
float	pass_red_index(int pixel_index)
{
	if (pixel_index % 4 == 0)
		return (pixel_index);
	if (pixel_index % 4 == 1)
		return (pixel_index - 1);
	if (pixel_index % 4 == 2)
		return (pixel_index - 2);
	if (pixel_index % 4 == 3)
		return (pixel_index - 3);
	return (pixel_index);
}
