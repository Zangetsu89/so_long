/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:10:02 by edawood           #+#    #+#             */
/*   Updated: 2022/12/01 18:18:13 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	free_2d(char **map)
{
	while (*map)
	{
		free(*map);
		map++;
	}
	return ;
}

// void	init_data(t_image_data *data)
// {
// 	obstacle_pickup(data);
// 	data->old_x = (data->img[PLAYER]->instances[0].x);
// 	data->old_y = (data->img[PLAYER]->instances[0].y);
// }

bool	free_array(mlx_image_t **arr, char *str, t_image_data *data)
{
	ft_putendl_fd("Error", STDOUT);
	ft_putendl_fd(str, STDOUT);
	while (arr)
	{
		free(arr);
		arr++;
	}
	free_2d(data->map);
	return (false);
}

void	free_close_window(t_image_data *data, void *var, char *str)
{
	ft_putendl_fd("Error\n", STDOUT);
	ft_putendl_fd(str, STDOUT);
	free(var);
	terminate(data);
}
