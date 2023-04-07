# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 12:50:21 by mkiflema          #+#    #+#              #
#    Updated: 2023/03/29 14:07:22 by mkiflema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name	= so_long

M_SRCS 	= so_long.c validate_arg.c
M_OBJS	= $(M_SRCS:.c=.o)

CC		= cc 
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f 

all: $(Name)

$(Name): $(M_OBJS)
	cd ./libft && make
	@$(CC) $(CFLAGS) $(M_OBJS) ./libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(Name)

clean:
	cd ./libft && make clean
	$(RM) $(M_OBJS)

fclean: clean
	cd ./libft && make fclean
	$(RM) $(Name)

re: fclean all