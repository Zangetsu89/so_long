/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:33:42 by edawood           #+#    #+#             */
/*   Updated: 2022/12/07 13:31:38 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	init_data(t_image_data *data)
{
	data->buflen = 1;
	data->fd = 0;
	data->map_name_len = 0;
	data->ext_len = 0;
	data->width = 0;
	data->height = 0;
	data->row_len = 0;
	data->rows_count = 0;
	data->player_count = 0;
	data->collectibles = 0;
	data->c_collected = 0;
	data->exits = 0;
	data->reachable_c = 0;
	data->reachable_e = 0;
	data->old_x = 0;
	data->old_y = 0;
	data->y = 0;
	data->x = 0;
}

int32_t	main(int32_t argc, char **argv)
{
	t_image_data	data;

	init_data(&data);
	if (argc == 2)
	{
		data.fd = open(argv[1], O_RDONLY);
		if (data.fd == -1)
			return (ft_putendl_fd("Error\nInvalid argument", STDOUT) \
					, EXIT_FAILURE);
		data.ext = ".ber";
		data.map_name_len = ft_strlen(argv[1]);
		data.ext_len = ft_strlen(data.ext);
		if (!check_ext(argv[1], ".ber"))
			return (EXIT_FAILURE);
		if (!check_map(&data))
			return (ft_putendl_fd("Error\nInvalid map input", STDOUT) \
					, EXIT_FAILURE);
	}
	else
		return (ft_putendl_fd("Error\nNo of args given is more/less than 2", \
		STDOUT), EXIT_FAILURE);
	if (!graphics(&data))
		free_2d(data.map);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
