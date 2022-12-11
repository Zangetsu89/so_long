/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:10:02 by edawood           #+#    #+#             */
/*   Updated: 2022/12/04 19:08:29 by edawood          ###   ########.fr       */
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

bool	free_array(mlx_image_t **arr, char *str, t_image_data *data)
{
	ft_putendl_fd("Error", STDOUT);
	ft_putendl_fd(str, STDOUT);
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(arr);
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
