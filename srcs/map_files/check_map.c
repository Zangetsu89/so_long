/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:36:35 by edawood           #+#    #+#             */
/*   Updated: 2022/12/04 15:12:16 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include <stdio.h>

void	flood_fill(ssize_t y, ssize_t x, t_image_data *data, char **map)
{
	if (map[y][x] == '1')
		return ;
	if (map[y][x] == 'E')
		data->reachable_e++;
	if (map[y][x] == 'C')
		data->reachable_c++;
	map[y][x] = '1';
	flood_fill (y, (x + 1), data, map);
	flood_fill (y, (x - 1), data, map);
	flood_fill ((y + 1), x, data, map);
	flood_fill ((y - 1), x, data, map);
}

static bool	check_walls(t_image_data *data, char **map, t_error *errors)
{
	ssize_t	i;

	i = 0;
	errors->no_walls = false;
	while (i < data->row_len)
	{
		if (map[0][i] != '1' || map[data->rows_count][i] != '1')
			return (errors->no_walls = true, false);
		i++;
	}
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][data->row_len - 1] != '1')
			return (errors->no_walls = true, false);
		i++;
	}
	return (true);
}

static bool	check_map_content(t_image_data *data, t_error *errors)
{
	size_t	i;

	i = 0;
	errors->invalid_map_input = false;
	errors->no_cpe = false;
	if (!(ft_strchr(data->map_data, 'C')) || !(ft_strchr(data->map_data, 'E')) \
	|| !(ft_strchr(data->map_data, 'P')))
		errors->no_cpe = true;
	while (data->map_data[i])
	{
		if (data->map_data[i] == 'C')
			data->collectibles++;
		if (data->map_data[i] == 'E')
			data->exits++;
		if (data->map_data[i] == 'P')
			data->player_count++;
		if (!(ft_strchr("01CEP\n", data->map_data[i++])))
			errors->invalid_map_input = true;
	}
	if (errors->no_cpe == true || errors->invalid_map_input == true)
		return (false);
	return (true);
}

static size_t	check_if_rectangular(t_image_data *data, char **map, \
													t_error *errors)
{
	ssize_t	i;

	i = 0;
	errors->not_rectangular = false;
	while (map[i + 1])
	{
		data->row_len = ft_strlen(map[i++]);
		if (data->row_len != (ssize_t)ft_strlen(map[i]))
			errors->not_rectangular = true;
	}
	data->rows_count = ft_strlen(map[i]);
	if (data->row_len == i)
		errors->not_rectangular = true;
	return (i);
}

char	**check_map(t_image_data *data, int32_t fd)
{
	t_error	errors;

	errors.error = false;
	errors.c_or_e_unreachable = false;
	data->map_data = read_file(fd);
	if (!data->map_data || data->map_data[0] == '\0')
		return (ft_putendl_fd("Error\nEmpty map", STDOUT), NULL);
	check_map_content(data, &errors);
	data->map = ft_split(((const char *)data->map_data), '\n');
	data->rows_count = check_if_rectangular(data, data->map, &errors);
	check_walls(data, data->map, &errors);
	get_player_position(data, data->map);
	error_handler(data, &errors);
	if (errors.error == true)
		return (free_2d(data->map), NULL);
	flood_fill(data->y, data->x, data, copyingmap(data));
	if (data->collectibles != data->reachable_c || \
	data->exits != data->reachable_e)
		errors.c_or_e_unreachable = true;
	error_handler(data, &errors);
	if (errors.error == true)
		return (free_2d(data->map), NULL);
	return (data->map);
}
