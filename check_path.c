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

int	dfs(t_data data, char **holder, char **visited,
		int y, int x)
{
	if (y == data.end[0] && x == data.end[1])
		return (1);
	if (visited[y][x] == '1')
		return (0);
	visited[y][x] = 1;
	if (is_valid_pos(data, holder, y, x + 1)
		&& dfs(data, holder, visited, y, x + 1))
		return (1);
	if (is_valid_pos(data, holder, y, x - 1)
		&& dfs(data, holder, visited, y, x - 1))
		return (1);
	if (is_valid_pos(data, holder, y + 1, x)
		&& dfs(data, holder, visited, y + 1, x))
		return (1);
	if (is_valid_pos(data, holder, y - 1, x)
		&& dfs(data, holder, visited, y - 1, x))
		return (1);
	visited[y][x] = 0;
	return (0);
}

int	is_valid_path(t_data data, char **holder)
{
	char	**visited;

	visited = NULL;
	allocate_space(&data, &visited);
	visited[0][0] = 0;
	return (dfs(data, holder, visited, data.start[0], data.start[1]));
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
