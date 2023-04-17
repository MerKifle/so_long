/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:27:56 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/17 21:17:54 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	so_long(t_data data)
{
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return ;
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * 64,
			data.height * 64 + 32, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return ;
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	create_images(&data);
	render(&data);
	mlx_key_hook(data.win_ptr, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
}

void	check_input_validity(char **argv, char **storage)
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
	if (!is_map_rectangular(*storage))
		display_message(storage, 5);
	close(fd);
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
		check_input_validity(argv, &storage);
		store_map(storage, &data);
		allocate_space(&data, &holder);
		make_area(data, storage, &holder);
		// if (!(is_valid_path(data, holder, 'E')))
		// 	display_message(6);
		so_long(data);
		free_array(holder);
		clear_and_close(&data);
	}
}
		// data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
		// 		&data.img.line_len, &data.img.endian);
