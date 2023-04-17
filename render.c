/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:15:50 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/17 21:18:22 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	push_image(t_data *data, char c, int y, int x)
{
	if (c == '1')
		mlx_put_image_to_window((*data).mlx_ptr, (*data).win_ptr,
			(*data).img.wall, 64 * x, 64 * y);
	if (c == '0')
		mlx_put_image_to_window((*data).mlx_ptr, (*data).win_ptr,
			(*data).img.empty, 64 * x, 64 * y);
	if (c == 'P')
		mlx_put_image_to_window((*data).mlx_ptr, (*data).win_ptr,
			(*data).img.player, 64 * x, 64 * y);
	if (c == 'C')
		mlx_put_image_to_window((*data).mlx_ptr, (*data).win_ptr,
			(*data).img.collectable, 64 * x, 64 * y);
	if (c == 'E')
		mlx_put_image_to_window((*data).mlx_ptr, (*data).win_ptr,
			(*data).img.exit, 64 * x, 64 * y);
	// int		img_width;
	// int		img_height;

	// (*data).img.mlx_img = mlx_xpm_file_to_image((*data).mlx_ptr, file_path,
	// 		&img_width, &img_height);
	// printf("height:%d width:%d", img_height, img_width);
}

void	create_images(t_data *data)
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

// void	get_image(char **file_path, t_data *data, int y, int x)
// {
// 	char	c;

// 	// c = data->storage[y][x];
// 	if (c == '1')
// 		(*file_path) = "textures/wall.xpm";
// 	else if (c == 'P')
// 	{
// 		// data->player_x = x;
// 		// data->player_y = y;
// 		(*file_path) = "textures/player.xpm";
// 	}
// 	else if (c == '0')
// 		(*file_path) = "textures/empty.xpm";
// 	else if (c == 'C')
// 		(*file_path) = "textures/collectable.xpm";
// 	else if (c == 'E')
// 		(*file_path) = "textures/end.xpm";
// }

void	render(t_data *data)
{
	char	*file_path;
	int		x;
	int		y;

	file_path = NULL;
	(void)file_path;
	if (data->win_ptr == NULL)
		return ;
	y = -1;
	while ((*data).storage[++y])
	{
		x = -1;
		while ((*data).storage[y][++x] && (*data).storage[y][x] != '\n')
		{
			// get_image(&file_path, data, y, x);
			push_image(data, data->storage[y][x], y, x);
		}
	}
}
