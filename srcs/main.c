/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:33:42 by edawood           #+#    #+#             */
/*   Updated: 2022/12/04 15:26:26 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int32_t	main(int32_t argc, char **argv)
{
	t_image_data	data;

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
		if (!check_map(&data, data.fd))
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
