/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:44:55 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/13 10:50:56 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_space(t_data *data, char ***container)
{
	int	i;

	(*container) = malloc(sizeof(char *) * (data->height + 1));
	if (!(*container))
		return ;
	i = -1;
	while (++i < data->height)
	{
		(*container)[i] = malloc(sizeof(char) * (data->width + 1));
		if (!(*container)[i])
			return ;
	}
}

static void	do_for_each_char(t_data, **data, char c)
{
	if (c == 'P')
	{
		(*data)->start[0] = i;
		(*data)->start[1] = j;
		(*data)->player_y = i;
		(*data)->player_x = j;
	}
	else if (c == 'E')
	{
		(*data)->end[0] = i;
		(*data)->end[1] = j;
	}
	else if (c == 'C')
		(*data)->collectables += 1;
}

void	fill_container(t_data **data, char *storage, char ***container, int i)
{
	int		j;
	int		width;

	width = -1;
	while (++i < (*data)->height)
	{
		j = 0;
		while (storage[++width] && storage[width] != '\n')
		{
			do_for_each_char(data, storage[width]);
			(*container)[i][j++] = storage[width];
		}
	}
	(*container)[i] = 0;
	(*data)->count_collectables = (*data)->collectables;
	free(storage);
}

void	store_map(char *storage, t_data *data)
{
	int		width;
	int		height;
	int		i;
	char	**container;

	i = -1;
	height = 1;
	container = NULL;
	while (storage[++i])
		if (storage[i] == '\n' && storage[i + 1] != '\0')
			height++;
	i = -1;
	width = 0;
	while (storage[++i] && storage[i] != '\n')
		width++;
	data->height = height;
	data->width = width;
	(*data)->collectables = 0;
	allocate_space(data, &container);
	fill_container(&data, storage, &container, -1);
	data->storage = container;
	data->numofmoves = 0;
}
