/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:57:31 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/19 11:55:14 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_start_and_exit(char **storage, int start, int exit, int colle)
{
	if (start < 1 || start > 1 || exit < 1 || exit > 1)
		display_message(storage, 3);
	else if (colle < 1)
		display_message(storage, 4);
}

void	validate_map_content(int fd, char **storage)
{
	int		start;
	int		end;
	char	*line;
	int		i;
	int		colle;

	start = 0;
	end = 0;
	colle = 0;
	line = NULL;
	while (get_next_line(fd, &line))
		*storage = ft_strjoin(*storage, line);
	free(line);
	i = -1;
	while ((*storage)[++i])
	{
		if ((*storage)[i] == 'P')
			start++;
		else if ((*storage)[i] == 'E')
			end++;
		else if ((*storage)[i] == 'C')
			colle++;
	}
	close(fd);
	check_start_and_exit(storage, start, end, colle);
}

int	is_map_rectangular(t_data *data)
{
	int	x;
	int	holder;
	int	y;

	x = 0;
	holder = 0;
	y = -1;
	while (data->storage[++y])
	{
		x = 0;
		while (data->storage[y][x])
			x++;
		if (holder == 0)
			holder = x;
		else if (holder != 0 && holder != x)
		{
			free_array(data->storage);
			return (0);
		}
	}
	return (1);
}

int	is_wall_valid(t_data data, char **storage)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (data.storage[++y] && y < data.height)
	{
		x = -1;
		while (data.storage[y][++x] && x < data.width)
		{
			if ((y == 0 || y == (data.height - 1)) && data.storage[y][x] != '1')
				return (0);
			if ((x == 0 || x == (data.width - 1)) && data.storage[y][x] != '1')
				return (0);
			c = data.storage[y][x];
			if (c != 'P' && c != '1' && c != '0' && c != 'C' && c != 'E')
			{
				free_array(data.storage);
				display_message(storage, 7);
			}
		}
	}
	return (1);
}

int	is_name_valid(char *pathname)
{
	int	i;

	while (*pathname && *pathname != '.')
		pathname++;
	i = ft_strlen(pathname);
	if (i < 4)
		i = 4;
	if (ft_strncmp(pathname, ".ber", i))
		return (0);
	return (1);
}
