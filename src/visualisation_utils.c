/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroos <mgroos@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:42:28 by mgroos            #+#    #+#             */
/*   Updated: 2025/12/10 10:56:43 by mgroos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h> // for uint32_t
#include <stdio.h>

/** Make a single unsgined int with the colour out of the rgba values
 * (a = alpha channel for transparency, set to 255 when not using) */
uint32_t get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/** Automatically sets opacity channel to 255, and takes R G B values from
 * int array.
 */
uint32_t get_rgba_from_array(int rgb[3])
{
	// printf("0: %i & ")	
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}
