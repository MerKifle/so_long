/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:15:50 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/11 10:39:07 by mkiflema         ###   ########.fr       */
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

void	get_image(char **file_path, t_data *data, int y, int x)
{
	char	c;

	c = data->storage[y][x];
	if (c == '1')
		(*file_path) = "textures/wall.xpm";
	else if (c == 'P')
	{
		data->player_x = x;
		data->player_y = y;
		(*file_path) = "textures/player.xpm";
	}
	else if (c == '0')
		(*file_path) = "textures/empty.xpm";
	else if (c == 'C')
		(*file_path) = "textures/collectable.xpm";
	else if (c == 'E')
		(*file_path) = "textures/end.xpm";
}

void	render(t_data *data)
{
	char	*file_path;
	int		x;
	int		y;

	file_path = NULL;
	if (data->win_ptr == NULL)
		return ;
	y = -1;
	while ((*data).storage[++y])
	{
		x = -1;
		while ((*data).storage[y][++x] && (*data).storage[y][x] != '\n')
		{
			get_image(&file_path, data, y, x);
			push_image(data, file_path, y, x);
		}
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr || *arr)
		return ;
	while (arr[i])
		i++;
	i--;
	while (i >= 0)
		free(arr[i--]);
	free(arr);
}
