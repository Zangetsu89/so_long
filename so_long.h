/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:01:25 by edawood           #+#    #+#             */
/*   Updated: 2022/12/01 21:20:07 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "./lib/MLX/include/MLX42/MLX42.h"
# include "./lib/libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>

# ifndef BUFFERSIZE
#  define BUFFERSIZE 30
# endif

# define PIXELS 32
# define MOVEMENT 5

# ifndef STDOUT
#  define STDOUT 2
# endif

typedef struct errors
{
	bool	error;
	bool	no_walls;
	bool	no_cpe;
	bool	invalid_map_input;
	bool	not_rectangular;
	bool	c_or_e_unreachable;
}	t_error;

typedef enum mlx_images
{
	PICKUP,
	PLAYER,
	MAP_EXIT,
	TILE,
	WALL,
	BG,
	IMG_COUNT,
}	t_images;

typedef enum string
{
	LIFE,
	MOVE,
	FRAME,
	ENDFRAME,
	STR_COUNT,
}	t_string;

typedef struct s_image_data {
	char			*ext;
	size_t			map_name_len;
	size_t			ext_len;
	int32_t			fd;
	int32_t			width;
	int32_t			height;
	char			*map_data;
	char			**map;
	ssize_t			row_len;
	ssize_t			rows_count;
	void			*mlx_win;
	size_t			player_count;
	size_t			collectibles;
	size_t			c_collected;
	size_t			exits;
	size_t			reachable_c;
	size_t			reachable_e;
	size_t			old_y;
	size_t			old_x;
	ssize_t			y;
	ssize_t			x;
	int32_t			count[STR_COUNT];
	mlx_t			*mlx;
	mlx_image_t		*img[IMG_COUNT];
	mlx_key_data_t	*keydata;
	xpm_t			*xpm[IMG_COUNT];
	mlx_texture_t	*textures[IMG_COUNT];
}				t_image_data;

char	*read_file(int32_t fd);
char	**check_map(t_image_data *data, int32_t fd);
void	flood_fill(ssize_t y, ssize_t x, t_image_data *data, char **map);
void	collectibles_count(t_image_data *data, char **map);
char	**copyingmap(t_image_data *data);
void	get_player_position(t_image_data *data, char **map);
bool	check_ext(char *file_name, char *ext);

bool	graphics(t_image_data *data);
bool	put_backg(t_image_data *data);
bool	images_to_window(t_image_data *data, size_t i);
void	free_close_window(t_image_data *data, void *var, char *str);
bool	free_array(mlx_image_t **arr, char *str, t_image_data *data);
void	free_2d(char **map);
void	hook(void *param);
void	movement(t_image_data *data, size_t x, size_t y);
void	collect(t_image_data *data, size_t x, size_t y);
void	movecounter(t_image_data *data, size_t y, size_t x);

void	error_handler(t_image_data *data, t_error *errors);
void	free_2d(char **map);
void	terminate(t_image_data *data);
#endif