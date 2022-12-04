/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:37:08 by edawood           #+#    #+#             */
/*   Updated: 2022/12/01 18:19:10 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	terminate(t_image_data *data)
{
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_2d(data->map);
	free(data->map_data);
	exit(0);
}

void	movement(t_image_data *data, size_t y, size_t x)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) \
						&& data->map[y + 1][x] != '1')
			data->img[PLAYER]->instances[0].y += PIXELS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A) \
							&& data->map[y][x - 1] != '1')
			data->img[PLAYER]->instances[0].x -= PIXELS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) \
							&& data->map[y][x + 1] != '1')
		data->img[PLAYER]->instances[0].x += PIXELS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) \
		&& data->map[y - 1][x] != '1')
		data->img[PLAYER]->instances[0].y -= PIXELS;
}

void	collect(t_image_data *data, size_t y, size_t x)
{
	size_t		i;

	i = 0;
	while (i < data->collectibles)
	{
		if ((x == (size_t)data->img[PICKUP]->instances[i].x) \
		&& (y == (size_t)data->img[PICKUP]->instances[i].y))
		{
			if (data->img[PICKUP]->instances[i].enabled == true)
			{
				data->c_collected++;
				ft_putstr_fd("No of collected: ", STDOUT);
				ft_putnbr_fd(data->c_collected, STDOUT);
				ft_putendl_fd("", STDOUT);
			}
			data->img[PICKUP]->instances[i].enabled = false;
		}
		i++;
	}
}

void	movecounter(t_image_data *data, size_t y, size_t x)
{
	if ((mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down \
		(data->mlx, MLX_KEY_D) || mlx_is_key_down (data->mlx, MLX_KEY_A) \
		|| mlx_is_key_down(data->mlx, MLX_KEY_W)) && \
		(x >= data->old_x + PIXELS || x <= data->old_x - PIXELS \
			|| y >= data->old_y + PIXELS || y <= data->old_y - PIXELS))
	{
		data->old_x = x;
		data->old_y = y;
		ft_putstr_fd("Move count is: ", STDOUT);
		ft_putnbr_fd(data->count[MOVE], STDOUT);
		ft_putendl_fd("", STDOUT);
		data->count[MOVE]++;
	}
}
