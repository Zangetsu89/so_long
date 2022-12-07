/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:29:18 by edawood           #+#    #+#             */
/*   Updated: 2022/12/07 13:38:28 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	init_errors(t_error *errors)
{
	errors->error = false;
	errors->no_cpe = false;
	errors->invalid_map_input = false;
	errors->not_rectangular = false;
	errors->no_walls = false;
	errors->c_or_e_unreachable = false;
}

void	error_handler(t_image_data *data, t_error *errors)
{
	if (errors->no_cpe == true || errors->invalid_map_input == true \
		|| errors->not_rectangular == true || errors->no_walls == true \
		|| errors->c_or_e_unreachable == true || data->rows_count == 0 \
		|| data->player_count > 1)
	{
		errors->error = true;
		ft_putendl_fd("Error", STDOUT);
	}
	if (errors->no_cpe == true)
		ft_putendl_fd("Does not contain at least 1 C, E or P", \
		STDOUT);
	if (data->player_count > 1)
		ft_putendl_fd("Contains more than 1 P", STDOUT);
	if (errors->invalid_map_input == true)
		ft_putendl_fd("Contains input other than 01CEP", STDOUT);
	if (errors->not_rectangular == true)
		ft_putendl_fd("Map is not rectangular", STDOUT);
	if (errors->no_walls == true)
		ft_putendl_fd("Map is not surrounded by walls", STDOUT);
	if (errors->c_or_e_unreachable == true)
		ft_putendl_fd("Not all C or E are reachable", STDOUT);
}
