/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:09:24 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/08 18:37:13 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_pos(t_data data, char **holder, int y, int x)
{
	if (y < 0 || y >= data.height || x < 0 || x >= data.width)
		return (0);
	if (holder[y][x] == '1')
		return (0);
	return (1);
}

int dfs(t_data data, char **holder, char target,
		int y, int x)
{
	if (y == data.end[0] && x == data.end[1])
		return (1);
	if (target == 'C' && holder[y][x] == 'C')
	{
		if (data.collectables != 0)
			data.collectables -= 1;
		if (data.collectables == 0)
			return (1);
	}
	if (holder[y][x] == 'E' && target == 'E')
		return (1);
	if (holder[y][x] != 'E')
		holder[y][x] = '1';
	if (is_valid_pos(data, holder, y, x + 1) && dfs(data, holder, target, y, x + 1))
		return (1);
	if (is_valid_pos(data, holder, y, x - 1) && dfs(data, holder, target, y, x - 1))
		return (1);
	if (is_valid_pos(data, holder, y + 1, x) && dfs(data, holder, target, y + 1, x))
		return (1);
	if (is_valid_pos(data, holder, y - 1, x) && dfs(data, holder, target, y - 1, x))
		return (1);
	return (0);
}

int is_valid_path(t_data data, char **holder, char target)
{
	return (dfs(data, holder, target, data.start[0], data.start[1]));
}

// int main() {
//     char grid[ROWS][COLS] = {
//         {'1', '1', '1', '1', '1'},
//         {'1', 'C', '0', 'P', '1'},
//         {'1', '1', '1', '0', '1'},
//         {'1', 'C', 'E', '0', '1'},
//         {'1', '1', '1', '1', '1'}
//     };
//     if (is_valid_path(grid))
//         printf("Valid path found!\n");
//     else
//         printf("No valid path found.\n");
//     return 0;
// }
