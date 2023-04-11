/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:50:09 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/11 11:43:01 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	change_pos(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->height || x < 0 || x >= data->width
		|| data->storage[data->player_y][data->player_x] != 'P')
		return ;
	if (data->storage[y][x] == '1')
		return ;
	data->storage[data->player_y][data->player_x] = '0';
	data->numofmoves = (int)data->numofmoves + 1;
	ft_printf("Num of moves: %d\n", data->numofmoves);
	if (data->storage[y][x] == 'E')
	{
		render(data);
		return ;
	}
	data->player_x = x;
	data->player_y = y;
	if (data->storage[y][x] == '0')
	{
		data->storage[y][x] = 'P';
		render(data);
	}
	else if (data->storage[y][x] == 'C')
	{
		data->storage[y][x] = 'P';
		render(data);
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 53)
	{
		free_array(data->storage);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		exit(0);
	}
	else if (keysym == 123 || keysym == 0)
		change_pos(data, data->player_y, data->player_x - 1);
	else if (keysym == 124 || keysym == 2)
		change_pos(data, data->player_y, data->player_x + 1);
	else if (keysym == 125 || keysym == 1)
		change_pos(data, data->player_y + 1, data->player_x);
	else if (keysym == 126 || keysym == 13)
		change_pos(data, data->player_y - 1, data->player_x);
	return (0);
}
