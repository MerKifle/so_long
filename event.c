/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:50:09 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/22 18:37:09 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_validity(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->height || x < 0 || x >= data->width
		|| data->storage[data->player_y][data->player_x] != 'P')
		return (0);
	if (data->storage[y][x] == '1' || (data->storage[y][x] == 'E'
			&& data->collectables != 0))
		return (0);
	return (1);
}

static void	erase_num_of_moves(t_data *data, int x, int y)
{
	char	*str;

	str = ft_strjoin(ft_strdup("Num of moves: "), ft_itoa(data->numofmoves));
	x--;
	while (++x < data->width)
		push_image(data, '0', y, x);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 0, y * 64 + 16,
		GREEN_PIXEL, str);
	if (str)
		free(str);
}

static void	change_pos(t_data *data, int y, int x)
{
	if (check_validity(data, y, x) == 0)
		return ;
	data->storage[data->player_y][data->player_x] = '0';
	data->numofmoves = (int)data->numofmoves + 1;
	ft_printf("Num of moves: %d\n", data->numofmoves);
	erase_num_of_moves(data, 0, data->height);
	if (data->storage[y][x] == 'E')
	{
		render(data);
		clear_and_close(data);
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
		data->collectables -= 1;
		data->storage[y][x] = 'P';
		render(data);
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 53 || keysym == 12)
		clear_and_close(data);
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
