/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:28:19 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/19 13:43:53 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

# define GREEN_PIXEL 0x00FF00

typedef struct s_img
{
	char	*addr;
	void	*wall;
	void	*player;
	void	*empty;
	void	*collectable;
	void	*exit;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**storage;
	int		width;
	int		height;
	int		start[2];
	int		player_y;
	int		player_x;
	int		numofmoves;
	int		collectables;
	t_img	img;
}	t_data;

// validate_arg
void	validate_map_content(int fd, char **storage);
int		is_map_rectangular(t_data *data);
int		is_wall_valid(t_data data, char **storage);
int		is_name_valid(char *pathname);

// free_and_close
void	free_array(char **arr);
void	clear_and_close(t_data *data);
void	display_message(char **storage, int value);
int		close_window(t_data *data);

//utils
void	allocate_space(t_data *data, char ***container);
void	store_map(char *storage, t_data *data);

// check_path
void	make_area(t_data data, char ***holder);
int		is_path_to_exit_vaild(t_data data, char **holder, int y, int x);
int		is_path_to_collec_valid(t_data data, char **holder);

// render
void	render(t_data *data);
void	push_image(t_data *data, char c, int y, int x);

// event
int		handle_keypress(int keysym, t_data *data);
#endif