/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:15:50 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/22 18:50:59 by mkiflema         ###   ########.fr       */
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
}

void	render(t_data *data)
{
	int		x;
	int		y;

	if (data->win_ptr == NULL)
		return ;
	y = -1;
	while ((*data).storage[++y])
	{
		x = -1;
		while ((*data).storage[y][++x] && (*data).storage[y][x] != '\n')
			push_image(data, data->storage[y][x], y, x);
	}
}
