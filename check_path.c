/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:09:24 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/20 20:20:46 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	make_area(t_data data, char ***holder)
{
	int	y;
	int	x;

	y = -1;
	while (data.storage[++y] && y < data.height)
	{
		x = -1;
		while (data.storage[y][++x] && x < data.width)
		{
			(*holder)[y][x] = data.storage[y][x];
		}
		(*holder)[y][x] = '\0';
	}
	(*holder)[y] = 0;
}

static int	check_collectable(t_data data, char **holder, int y, int x)
{
	if (y < 0 || y >= data.height || x < 0 || x >= data.width
		|| holder[y][x] == '1' || holder[y][x] == 'E')
		return (0);
	if (holder[y][x] == 'P')
		return (1);
	holder[y][x] = '1';
	if (check_collectable(data, holder, y, x + 1))
		return (1);
	if (check_collectable(data, holder, y, x - 1))
		return (1);
	if (check_collectable(data, holder, y + 1, x))
		return (1);
	if (check_collectable(data, holder, y - 1, x))
		return (1);
	return (0);
}

int	is_path_to_exit_vaild(t_data data, char **holder, int y, int x)
{
	if (y < 0 || y >= data.height || x < 0 || x >= data.width
		|| holder[y][x] == '1')
		return (0);
	if (holder[y][x] == 'E')
		return (1);
	holder[y][x] = '1';
	if (is_path_to_exit_vaild(data, holder, y, x + 1))
		return (1);
	if (is_path_to_exit_vaild(data, holder, y, x - 1))
		return (1);
	if (is_path_to_exit_vaild(data, holder, y + 1, x))
		return (1);
	if (is_path_to_exit_vaild(data, holder, y - 1, x))
		return (1);
	return (0);
}

int	is_path_to_collec_valid(t_data data, char **holder)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data.height)
	{
		x = -1;
		while (++x < data.width)
		{
			if (data.storage[y][x] == 'C')
			{
				free_array(holder);
				allocate_space(&data, &holder);
				make_area(data, &holder);
				if (!holder || !check_collectable(data, holder, y, x))
				{
					free_array(holder);
					free_array(data.storage);
					return (0);
				}
			}
		}
	}
	free_array(holder);
	return (1);
}
