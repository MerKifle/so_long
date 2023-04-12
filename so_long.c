/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:27:56 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/11 11:39:32 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_container(t_data **data, char *storage,
							char ***container, int i)
{
	int		j;
	int		width;
	int		collectables;

	width = -1;
	collectables = 0;
	while (++i < (*data)->height)
	{
		j = 0;
		while (storage[++width] && storage[width] != '\n')
		{
			if (storage[width] == 'P')
			{
				(*data)->start[0] = i;
				(*data)->start[1] = j;
				(*data)->player_y = i;
				(*data)->player_x = j;
			}
			else if (storage[width] == 'E')
			{
				(*data)->end[0] = i;
				(*data)->end[1] = j;
			}
			else if (storage[width] == 'C')
				collectables += 1;
			(*container)[i][j++] = storage[width];
		}
	}
	(*container)[i] = 0;
	(*data)->collectables = collectables;
	free(storage);
}

void	allocate_space(t_data *data, char ***container)
{
	int	i;

	(*container) = malloc(sizeof(char *) * (data->height + 1));
	if (!(*container))
		return ;
	i = -1;
	while (++i < data->height)
	{
		(*container)[i] = malloc(sizeof(char) * (data->width + 1));
		if (!(*container)[i])
			return ;
	}
}

char	**store_map(char *storage, t_data *data)
{
	int		width;
	int		height;
	int		i;
	char	**container;

	i = -1;
	height = 1;
	container = NULL;
	while (storage[++i])
		if (storage[i] == '\n' && storage[i + 1] != '\0')
			height++;
	i = -1;
	width = 0;
	while (storage[++i] && storage[i] != '\n')
		width++;
	data->height = height;
	data->width = width;
	allocate_space(data, &container);
	fill_container(&data, storage, &container, -1);
	data->storage = container;
	return (container);
}

void	so_long(t_data data)
{
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return ;
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * 64,
			data.height * 64, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return ;
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	render(&data);
	data.numofmoves = 0;
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
}


int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	char	*storage;
	// char	**holder;
	storage = NULL;
	// holder = NULL;

	if (argc == 2)
	{
		if (!argv[1] || !argv[1][0])
			display_message(0);
		if (!is_name_valid(argv[1]))
			display_message(1);
		fd = open(argv[1], O_RDONLY, 0777);
		if (fd == -1)
			display_message(2);
		validate_map_content(fd, &storage);
		if (!is_map_rectangular(storage))
			display_message(5);
		// allocate_space(&data, &holder);
		store_map(storage, &data);
		// free_array((void **)holder);
		// if (!(is_valid_path(data, holder)))
		// 	display_message(6);
		// else
		// 	printf("valid path");
	 	so_long(data);
		mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
	}
}
		// data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
		// 		&data.img.line_len, &data.img.endian);
