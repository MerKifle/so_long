/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:15:50 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/08 18:36:25 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	push_image(t_data *data, char *file_path, int y, int x)
{
	int		img_width;
	int		img_height;

	(*data).img.mlx_img = mlx_xpm_file_to_image((*data).mlx_ptr, file_path,
			&img_width, &img_height);
	mlx_put_image_to_window((*data).mlx_ptr, (*data).win_ptr,
		(*data).img.mlx_img, img_width * x, img_width * y);
}

void	get_image(char **file_path, char c)
{
	if (c == '1')
		(*file_path) = "textures/wall_1.xpm";
	else if (c == 'P')
		(*file_path) = "textures/start.xpm";
	else if (c == '0')
		(*file_path) = "textures/empty.xpm";
	else if (c == 'C')
		(*file_path) = "textures/collectable.xpm";
	else if (c == 'E')
		(*file_path) = "textures/end.xpm";
}

int	render(t_data *data)
{
	char	*file_path;
	int		x;
	int		y;

	file_path = NULL;
	if (data->win_ptr == NULL)
		return (1);
	y = -1;
	while ((*data).storage[++y])
	{
		x = -1;
		while ((*data).storage[y][++x] && (*data).storage[y][x] != '\n')
		{
			get_image(&file_path, (*data).storage[y][x]);
			push_image(data, file_path, y, x);
		}
	}
	file_path = "textures/player.xpm";
	push_image(data, file_path, data->start[0], data->start[1]);
	return (0);
}
