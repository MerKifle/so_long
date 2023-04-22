# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 12:50:21 by mkiflema          #+#    #+#              #
#    Updated: 2023/04/22 13:35:26 by mkiflema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name	= so_long

M_SRCS 	= so_long.c validate_arg.c utils.c render.c event.c check_path.c free_and_close.c
M_OBJS	= $(M_SRCS:.c=.o)

CC		= cc 
CFLAGS	= -Wall -Wextra -Werror 
RM		= rm -f 

all: $(Name)

$(Name): $(M_OBJS)
	cd ./libft && make
	cd ./mlx && make
	@$(CC) $(CFLAGS) $(M_OBJS) ./libft/libft.a  -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(Name)

clean:
	cd ./libft && make clean
	cd ./mlx && make clean
	$(RM) $(M_OBJS)

fclean: clean
	cd ./libft && make fclean
	$(RM) $(Name)

norm: 
	norminette *.h *.c ./libft/*.c ./libft/*.h

re: fclean 	all