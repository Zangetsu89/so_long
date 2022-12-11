/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:38:56 by edawood           #+#    #+#             */
/*   Updated: 2022/12/07 13:42:41 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

bool	texture_to_image(t_image_data *data, mlx_texture_t **textures, \
													mlx_image_t **img)
{
	img[BG] = mlx_texture_to_image(data->mlx, textures[BG]);
	img[PLAYER] = mlx_texture_to_image(data->mlx, textures[PLAYER]);
	img[TILE] = mlx_texture_to_image(data->mlx, textures[TILE]);
	img[WALL] = mlx_texture_to_image(data->mlx, textures[WALL]);
	img[PICKUP] = mlx_texture_to_image(data->mlx, textures[PICKUP]);
	img[MAP_EXIT] = mlx_texture_to_image(data->mlx, textures[MAP_EXIT]);
	if (!img[BG] || !img[PLAYER] || !img[TILE] || !img[WALL] || !img[PICKUP] \
	|| !img[MAP_EXIT])
		return (ft_putendl_fd("Texture to image failed", STDOUT), false);
	return (true);
}

bool	loading_images(mlx_texture_t **textures)
{
	textures[TILE] = mlx_load_png("./srcs/textures/obstical.png");
	if (!textures[TILE])
		return (ft_putendl_fd("tile was not found", STDOUT), false);
	textures[WALL] = mlx_load_png("./srcs/textures/space_wall.png");
	if (!textures[WALL])
		return (ft_putendl_fd("wall was not found", STDOUT), false);
	textures[PICKUP] = mlx_load_png("./srcs/textures/pickup.png");
	if (!textures[PICKUP])
		return (ft_putendl_fd("pickup was not found", STDOUT), false);
	textures[MAP_EXIT] = mlx_load_png("./srcs/textures/big_ship.png");
	if (!textures[MAP_EXIT])
		return (ft_putendl_fd("exit was not found", STDOUT), false);
	textures[PLAYER] = mlx_load_png("./srcs/textures/player.png");
	if (!textures[PLAYER])
		return (ft_putendl_fd("player texture was not found", STDOUT), false);
	return (true);
}

static bool	init_graphics(t_image_data *data)
{
	data->width = data->row_len * PIXELS;
	data->height = (data->rows_count * (PIXELS)) + PIXELS;
	if (!put_backg(data))
	{
		ft_putendl_fd("NO BG", STDOUT);
		return (NULL);
	}
	if (!(loading_images(data->textures)) || \
	!(texture_to_image(data, data->textures, data->img)) \
	|| !(images_to_window(data, 0)))
		return (false);
	if (mlx_image_to_window(data->mlx, data->img[BG], 200, 200) == -1)
		return (free_close_window(data, data->img[BG], \
					"image_to_window failed"), false);
	mlx_set_instance_depth(data->img[BG]->instances, -999);
	return (true);
}

void	hook(void *param)
{
	size_t			x;
	size_t			y;
	t_image_data	*data2;

	data2 = param;
	x = (data2->img[PLAYER]->instances[0].x / PIXELS);
	y = (data2->img[PLAYER]->instances[0].y / PIXELS);
	if ((data2->map[y][x] == 'E' && data2->c_collected >= data2->collectibles))
		terminate(param);
	else
	{
		if (mlx_is_key_down(data2->mlx, MLX_KEY_ESCAPE))
			terminate(param);
		movement(data2, y, x);
		x = (data2->img[PLAYER]->instances[0].x);
		y = (data2->img[PLAYER]->instances[0].y);
		collect(data2, y, x);
		movecounter(data2, y, x);
		data2->count[FRAME]++;
	}
}

bool	graphics(t_image_data *data)
{
	if (!init_graphics(data))
		return (false);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	return (true);
}
