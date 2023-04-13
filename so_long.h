/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:28:19 by mkiflema          #+#    #+#             */
/*   Updated: 2023/04/13 11:04:45 by mkiflema         ###   ########.fr       */
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
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx/mlx.h"
# include "mlx/mlx.h"
# include "libft/libft.h"

# define WINDOW_WIDTH 900
# define WINDOW_HEIGHT 400

# define MLX_ERROR 1

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define WHITE_PIXEL 0xFFFFFF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
}	t_img;

typedef struct s_cur
{
	int	y;
	int	x;
}		t_cur;

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
	int		end[2];
	int		numofmoves;
	int		collectables;
	int		count_collectables;
	t_img	img;
	t_cur	cur;
	int		cur_img;
}	t_data;

// so_long
void	allocate_space(t_data *data, char ***container);
// validate_arg
int		validate_map_content(int fd, char **storage);
int		is_map_rectangular(char *map);
int		is_wall_valid(char *str);
int		is_name_valid(char *pathname);
void	display_message(int value);

//utils
void	allocate_space(t_data *data, char ***container);
// check_path
int		is_valid_path(t_data data, char **holder, char target);
void	make_area(t_data data, char *storage, char ***holder);

// render
void	render(t_data *data);
void	free_array(char **arr);

// event
int		handle_keypress(int keysym, t_data *data);
#endif