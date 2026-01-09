/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:05:25 by inikelsk          #+#    #+#             */
/*   Updated: 2026/01/09 10:37:49 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Draw a square of given size and color at given position on given image. */
static void	draw_rect(mlx_image_t *img, t_vector pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (pos.x + i < img->width && pos.y + j < img->height)
				mlx_put_pixel(img, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

/* Draw the walls of the minimap onto the minimap background image. */
static void	draw_minimap_walls(t_data *data)
{
	int			x;
	int			y;
	t_vector	pos;
	int			size;

	y = 0;
	if (data->visuals.mm_scale < 1)
		size = 1;
	else
		size = (int)data->visuals.mm_scale;
	while (y < data->scene.map.height)
	{
		x = 0;
		while (x < data->scene.map.width)
		{
			if (data->scene.map.grid[y][x] == '1')
			{
				pos.x = x * data->visuals.mm_scale;
				pos.y = y * data->visuals.mm_scale;
				draw_rect(data->visuals.mm_bg, pos, size + 1, MM_COLOR_WALL);
			}
			x++;
		}
		y++;
	}
}

/* Initialize the minimap: create the background and player images,
   draw the walls, and place the images in the window. */
void	init_minimap(t_data *data)
{
	float	scale_x;
	float	scale_y;
	int		p_size;

	scale_x = (float)MINIMAP_W / data->scene.map.width;
	scale_y = (float)MINIMAP_H / data->scene.map.height;
	if (scale_x < scale_y)
		data->visuals.mm_scale = scale_x;
	else
		data->visuals.mm_scale = scale_y;
	data->visuals.mm_bg = mlx_new_image(data->visuals.mlx,
			data->scene.map.width * data->visuals.mm_scale,
			data->scene.map.height * data->visuals.mm_scale);
	draw_minimap_walls(data);
	if (data->visuals.mm_scale > 4)
		p_size = data->visuals.mm_scale;
	else
		p_size = 10;
	data->visuals.mm_player = mlx_new_image(data->visuals.mlx, p_size, p_size);
	draw_rect(data->visuals.mm_player, (t_vector){0, 0}, p_size, MM_COLOR_DOT);
	mlx_image_to_window(data->visuals.mlx, data->visuals.mm_bg,
		SCREEN_WIDTH - data->visuals.mm_bg->width - 10, 10);
	mlx_image_to_window(data->visuals.mlx, data->visuals.mm_player, 0, 0);
	data->visuals.mm_active = true;
	update_minimap(data);
}

/* Update the minimap player position based on the player's grid position. */
void	update_minimap(t_data *data)
{
	int	x;
	int	y;
	int	offset_x;

	if (!data->visuals.mm_active)
		return ;
	offset_x = SCREEN_WIDTH - data->visuals.mm_bg->width - 10;
	x = (data->player.x_grid * data->visuals.mm_scale) - \
	(data->visuals.mm_player->width / 2) + offset_x;
	y = (data->player.y_grid * data->visuals.mm_scale) - \
	(data->visuals.mm_player->height / 2) + 10;
	data->visuals.mm_player->instances[0].x = x;
	data->visuals.mm_player->instances[0].y = y;
	mlx_set_instance_depth(&data->visuals.mm_bg->instances[0], 11);
	mlx_set_instance_depth(&data->visuals.mm_player->instances[0], 10);
}

/* Toggle the minimap's visibility on and off. */
void	toggle_minimap(t_data *data)
{
	data->visuals.mm_active = !data->visuals.mm_active;
	data->visuals.mm_bg->enabled = data->visuals.mm_active;
	data->visuals.mm_player->enabled = data->visuals.mm_active;
}
