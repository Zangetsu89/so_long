/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_to_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:07:17 by edawood           #+#    #+#             */
/*   Updated: 2022/12/07 13:45:21 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

static bool	walls_and_tiles(t_image_data *data, size_t i, ssize_t x, ssize_t y)
{
	if (data->map_data[i] == '1')
	{
		if (x == 0 || y == 0 || y == data->rows_count \
							|| x == data->row_len - 1)
		{
			if (mlx_image_to_window(data->mlx, data->img[WALL], \
												x * PIXELS, y * PIXELS) == -1)
				return (free_array(data->img, "image_to_window failed", \
															data), false);
		}
		else
		{
			if (mlx_image_to_window(data->mlx, data->img[TILE], \
												x * PIXELS, y * PIXELS) == -1)
				return (free_array(data->img, "image_to_window failed", \
															data), false);
		}
	}
	return (true);
}

static bool	images_to_window2(t_image_data *data, size_t x, size_t y, \
													int32_t macro)
{
	if (macro >= PICKUP && macro <= MAP_EXIT)
	{
		if (mlx_image_to_window(data->mlx, data->img[macro], \
												x * PIXELS, y * PIXELS) == -1)
			return (free_array(data->img, "image_to_window failed", \
														data), false);
	}
	return (true);
}

bool	images_to_window(t_image_data *data, size_t i)
{
	size_t	x;
	size_t	y;
	int32_t	macro;

	while (data->map_data[i])
	{
		macro = MAP_EXIT + 1;
		x = i % (data->row_len + 1);
		y = i / (data->row_len + 1);
		if (data->map_data[i] == '1')
		{
			if (!(walls_and_tiles(data, i, x, y)))
				return (false);
		}
		else if (data->map_data[i] == 'C')
			macro = PICKUP;
		else if (data->map_data[i] == 'P')
			macro = PLAYER;
		else if (data->map[y][x] == 'E')
			macro = MAP_EXIT;
		if (!(images_to_window2(data, x, y, macro)))
			return (false);
		i++;
	}
	return (true);
}

bool	init_mlx(t_image_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "Spacy Bleach", true);
	if (!data->mlx)
		return (false);
	data->textures[BG] = mlx_load_png("./srcs/textures/bg2.png");
	if (!data->textures[BG])
		return (false);
	data->img[BG] = mlx_texture_to_image(data->mlx, data->textures[BG]);
	if (!data->img[BG])
		return (false);
	return (true);
}

bool	put_backg(t_image_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (!init_mlx(data))
		return (false);
	while (y < data->rows_count * PIXELS)
	{
		x = 0;
		while (x < data->row_len * PIXELS)
		{
			mlx_image_to_window(data->mlx, data->img[BG], \
								x * PIXELS, y * PIXELS);
			if (! mlx_image_to_window(data->mlx, \
			data->img[BG], x * PIXELS, y * PIXELS))
				return (false);
			x++;
		}		
		y++;
		x = 0;
	}
	return (true);
}
