/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:27:56 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/19 13:08:26 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	create_images(t_data *data)
{
	int		img_width;
	int		img_height;
	char	*file_path;

	file_path = "textures/wall.xpm";
	data->img.wall = mlx_xpm_file_to_image((*data).mlx_ptr, file_path,
			&img_width, &img_height);
	file_path = "textures/empty.xpm";
	data->img.empty = mlx_xpm_file_to_image((*data).mlx_ptr, file_path,
			&img_width, &img_height);
	file_path = "textures/player.xpm";
	data->img.player = mlx_xpm_file_to_image((*data).mlx_ptr, file_path,
			&img_width, &img_height);
	file_path = "textures/collectable.xpm";
	data->img.collectable = mlx_xpm_file_to_image((*data).mlx_ptr,
			file_path, &img_width, &img_height);
	file_path = "textures/end.xpm";
	data->img.exit = mlx_xpm_file_to_image((*data).mlx_ptr,
			file_path, &img_width, &img_height);
}

void	so_long(t_data data)
{
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return ;
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * 64,
			data.height * 64 + 32, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return ;
	}
	create_images(&data);
	render(&data);
	mlx_key_hook(data.win_ptr, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_window, &data);
	mlx_loop(data.mlx_ptr);
}

static void	check_input_validity(char **argv, char **storage, t_data *data)
{
	int	fd;

	if (!argv[1] || !argv[1][0])
		display_message(storage, 0);
	if (!is_name_valid(argv[1]))
		display_message(storage, 1);
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		display_message(storage, 2);
	validate_map_content(fd, storage);
	close(fd);
	store_map(*storage, data);
	if (!is_map_rectangular(data))
		display_message(storage, 5);
	if (!is_wall_valid(*data, storage))
	{
		free_array(data->storage);
		display_message(storage, 6);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*storage;
	char	**holder;

	storage = NULL;
	holder = NULL;
	if (argc == 2)
	{
		check_input_validity(argv, &storage, &data);
		allocate_space(&data, &holder);
		make_area(data, &holder);
		if (!is_path_to_exit_vaild(data, holder, data.start[0], data.start[1]))
		{
			free_array(holder);
			free_array(data.storage);
			display_message(&storage, 8);
		}
		if (!is_path_to_collec_valid(data, holder))
			display_message(&storage, 8);
		if (storage)
			free(storage);
		so_long(data);
		clear_and_close(&data);
	}
}
