/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:44:55 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/19 12:08:15 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_space(t_data *data, char ***container)
{
	int	i;

	(*container) = malloc(sizeof(char *) * (data->height + 1));
	if (!(*container))
	{
		free_array((*container));
		return ;
	}
	i = -1;
	while (++i < data->height)
	{
		(*container)[i] = malloc(sizeof(char) * (data->width + 1));
		if (!(*container)[i])
		{
			free((*container)[i]);
			return ;
		}
	}
}

void	fill_container(t_data **data, char *storage, int i)
{
	int		j;
	int		width;

	width = -1;
	if (!(*data)->storage || !(*data)->storage[0])
		return ;
	while (++i < (*data)->height)
	{
		j = 0;
		while (storage[++width] && storage[width] != '\n')
		{
			if (storage[width] == 'P')
			{
				(*data)->start[0] = i;
				(*data)->start[1] = j;
				(*data)->player_y = i;
				(*data)->player_x = j;
			}
			else if (storage[width] == 'C')
				(*data)->collectables += 1;
			(*data)->storage[i][j++] = storage[width];
		}
		(*data)->storage[i][j] = '\0';
	}
	(*data)->storage[i] = 0;
}

void	store_map(char *storage, t_data *data)
{
	int		width;
	int		height;
	int		i;

	i = -1;
	height = 1;
	while (storage[++i])
		if (storage[i] == '\n' && storage[i + 1] != '\0')
			height++;
	i = -1;
	width = 0;
	while (storage[++i] && storage[i] != '\n')
		width++;
	data->height = height;
	data->width = width;
	data->collectables = 0;
	data->storage = NULL;
	allocate_space(data, &data->storage);
	fill_container(&data, storage, -1);
	data->numofmoves = 0;
}
