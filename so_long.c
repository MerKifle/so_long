/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:27:56 by mkiflema          #+#    #+#             */
/*   Updated: 2023/03/31 21:34:58 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	so_long(char *storage)
{
	char	**holder;
	int		width;
	int		height;
	int		i;
	int		j;

	i = -1;
	height = 0;
	while (storage[++i])
		if (storage[i] == '\n')
			height++;
	i = -1;
	width = 0;
	while (storage[++i] && storage[i] != '\n')
		width++;
	holder = malloc(sizeof(char *) * (height + 1));
	if (!holder)
		return ;
	i = -1;
	while (++i < height)
	{
		printf("i is here: %d: %d\n", i, height);
		holder[i] = malloc(sizeof(char) * (width + 1));
		if (!holder[i])
			return ;
	}
	i = -1;
	width = 0;
	while (++i < height)
	{
		j = 0;
		while (storage[++width] && storage[width] != '\n')
			holder[i][j++] = storage[width];
		width++;
	}
	printf("outside: %d: %d\n", i, height);
	printf("here its: %c", holder[3][2]);
}

int	main(int argc, char **argv)
{
	// t_data	data;
	int		fd;
	char	*storage;

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
			display_message(4);
		so_long(storage);
	}

	// data.mlx_ptr = mlx_init();
	// if (data.mlx_ptr == NULL)
	// 	return (MLX_ERROR);
	// data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH,
	// 		WINDOW_HEIGHT, "my window");
	// if (data.win_ptr == NULL)
	// {
	// 	free(data.win_ptr);
	// 	return (MLX_ERROR);
	// }
	// data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
	// 		&data.img.line_len, &data.img.endian);
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	// mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	// mlx_loop(data.mlx_ptr);
	// mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	// mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	// free(data.mlx_ptr);
}
