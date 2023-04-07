/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:57:31 by mkiflema          #+#    #+#             */
/*   Updated: 2023/03/29 18:28:19 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map_content(int fd, char **storage)
{
	int		start;
	int		end;
	char	*line;
	int		i;
	int		colle;

	start = 0;
	end = 0;
	colle = 0;
	while (get_next_line(fd, &line))
		*storage = ft_strjoin(*storage, line);
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
	if (start > 1 || end > 1)
		display_message(3);
	else if (colle < 1)
		display_message(4);
	return (1);
}

int	is_map_rectangular(char *map)
{
	int	width;
	int	height;
	int	holder;
	int	i;

	width = 0;
	height = 1;
	i = -1;
	while (map[++i])
	{
		if (map[i] == '\n')
		{
			map = ft_strdup(map + i + 1);
			width = i;
			height++;
			i = -1;
		}
		if (!holder)
			holder = width;
		else if (holder != 0 && holder != width)
			return (0);
	}
	if (height == width)
		return (0);
	return (1);
}

int	is_wall_valid(char *str)
{
	int		wall;
	int		i;

	wall = 0;
	i = -1;
	while (str[++i])
	{
		if (i == 0 && str[i] == '1')
			wall++;
		if (str[i] == '1' && str[i + 1] == '\n')
			wall++;
		if (str[i] == '\n' && wall == 2)
		{
			str = ft_strdup(str + i + 1);
			i = -1;
			wall = 0;
		}
		if (str[i] == '\n' && wall != 2)
			return (0);
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

void	display_message(int value)
{
	if (value == 0)
		ft_putstr("Error\ninvalid file!");
	else if (value == 1)
		ft_putstr("Error\nfilename is not valid!");
	else if (value == 2)
		ft_putstr("Error\nfile path is not valid!");
	else if (value == 3)
		ft_putstr("Error\nstart or exit are dublicated!");
	else if (value == 4)
		ft_putstr("Error\ngame should have at leat one collectable!");
	exit(0);
}

