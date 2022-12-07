/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:34:23 by edawood           #+#    #+#             */
/*   Updated: 2022/12/07 13:37:00 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

char	*read_file(t_image_data *data)
{
	// int32_t	buflen;
	char	*line;
	char	*buf;

	// buflen = 1;
	line = ft_calloc(1, 1);
	buf = malloc(BUFFERSIZE + 1 * sizeof(char));
	while (data->buflen > 0)
	{
		data->buflen = read(data->fd, buf, BUFFERSIZE);
		if (data->buflen <= 0)
			free (buf);
		if (data->buflen == 0)
			return (line);
		if (data->buflen < 0)
			return (NULL);
		buf[data->buflen] = '\0';
		line = ft_strjoin(line, buf);
	}
	close(data->fd);
	return (line);
}

char	**copyingmap(t_image_data *data)
{
	int		i;
	char	**copymap;

	copymap = (char **) malloc(sizeof(char *) * (data->row_len + 1));
	if (!copymap)
		free(copymap);
	i = 0;
	while (data->map[i])
	{
		copymap[i] = ft_strdup(data->map[i]);
		i++;
	}
	copymap[i] = NULL;
	return (copymap);
}

void	get_player_position(t_image_data *data, char **map)
{
	ssize_t	i;
	ssize_t	j;

	j = 0;
	while (j < data->rows_count)
	{
		i = 0;
		while (i < data->row_len)
		{
			if (map[j][i] == 'P')
			{
				data->x = i;
				data->y = j;
				return ;
			}
			i++;
		}
		j++;
	}
}

bool	check_ext(char *file_name, char *ext)
{
	size_t	ext_len;
	size_t	name_len;

	if (!ext)
		return (ft_putendl_fd("Error\nYou are not checking for an extension", \
				STDOUT), false);
	if (!file_name)
		return (ft_putendl_fd("Error\nThere is no file name", \
				STDOUT), false);
	ext_len = ft_strlen(ext);
	name_len = ft_strlen(file_name);
	while (ext_len > 0)
	{
		if (file_name[name_len--] != ext[ext_len--])
			return (ft_putendl_fd("Error\nWrong file extension", \
					STDOUT), false);
	}
	return (true);
}
