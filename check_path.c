/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:09:24 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/17 18:42:51 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	make_area(t_data data, char *storage, char ***holder)
{
	int	j;
	int	width;
	int	i;

	width = -1;
	i = -1;
	while (++i < data.height)
	{
		j = 0;
		while (storage[++width] && storage[width] != '\n')
		{
			(*holder)[i][j++] = storage[width];
		}
	}
	(*holder)[i] = 0;
}

static int	dfs(t_data data, char **holder, char target, t_cur cur)
{
	if (cur.y < 0 || cur.y >= data.height || cur.x < 0 || cur.x >= data.width)
		return (0);
	else if (holder[cur.y][cur.x] == '1'
		|| (holder[cur.y][cur.x] != 'E' && data.count_collectables != 0))
		return (0);
	else if (cur.y == data.end[0] && cur.x == data.end[1])
		return (1);
	if (holder[cur.y][cur.x] == 'E' && target == 'E')
		return (1);
	else if (target == 'C' && holder[cur.y][cur.x] == 'C')
		if (data.count_collectables != 0)
			data.count_collectables -= 1;
	if (data.count_collectables == 0)
		return (1);
	if (holder[cur.y][cur.x] != 'E')
		holder[cur.y][cur.x] = '1';
	if (dfs(data, holder, target, (t_cur){cur.y, cur.x + 1}))
		return (1);
	if (dfs(data, holder, target, (t_cur){cur.y, cur.x - 1}))
		return (1);
	if (dfs(data, holder, target, (t_cur){cur.y + 1, cur.x}))
		return (1);
	if (dfs(data, holder, target, (t_cur){cur.y - 1, cur.x}))
		return (1);
	return (0);
}

int	is_valid_path(t_data data, char **holder, char target)
{
	return (dfs(data, holder, target,
			(t_cur){data.start[0], data.start[1]}));
}
