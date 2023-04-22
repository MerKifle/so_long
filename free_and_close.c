/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:25:07 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/22 13:54:01 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !(*arr))
		return ;
	while (arr[i])
		i++;
	i--;
	while (i >= 0)
		free(arr[i--]);
	free(arr);
}

void	clear_and_close(t_data *data)
{
	free_array(data->storage);
	if (data->img.wall)
		mlx_destroy_image(data->mlx_ptr, data->img.wall);
	if (data->img.player)
		mlx_destroy_image(data->mlx_ptr, data->img.player);
	if (data->img.empty)
		mlx_destroy_image(data->mlx_ptr, data->img.empty);
	if (data->img.exit)
		mlx_destroy_image(data->mlx_ptr, data->img.exit);
	if (data->img.collectable)
		mlx_destroy_image(data->mlx_ptr, data->img.collectable);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int	close_window(t_data *data)
{
	clear_and_close(data);
	return (0);
}

void	display_message(char **storage, int value)
{
	if (value == -1)
		ft_putstr("Error\nfile does not exist/empty/invalid content!");
	if (value == 0)
		ft_putstr("Error\ninvalid file!");
	else if (value == 1)
		ft_putstr("Error\nfilename is not valid!");
	else if (value == 2)
		ft_putstr("Error\nfile is not found!");
	else if (value == 3)
		ft_putstr("Error\nplayer or/and exit are dublicated!");
	else if (value == 4)
		ft_putstr("Error\ngame should have at least one collectable!");
	else if (value == 5)
		ft_putstr("Error\nmap is not rectangular!");
	else if (value == 6)
		ft_putstr("Error\nwall is not valid");
	else if (value == 7)
		ft_putstr("Error\ninvalid map content!");
	else if (value == 8)
		ft_putstr("Error\npath is not valid!");
	if (*storage)
		free(*storage);
	exit(0);
}
