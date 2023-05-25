# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seyang <seyang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 17:52:39 by segan             #+#    #+#              #
#    Updated: 2023/05/23 15:38:19 by seyang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror

FWKFLAGS = -framework OpenGl -framework AppKit

HDRFLAGS = -I /usr/local/include

LIBFLAGS = -L /usr/Local/lib/ -l mlx

DEBUG = -g -fsanitize=address

SRCS = cub3d.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	# make -C ./libft
	$(CC) $(DEBUG) $(FWKFLAGS) $(HDRFLAGS) $(LIBFLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

clean :
	# make clean -C ./libft
	rm -f $(OBJS)

fclean :
	# make fclean -C ./libft
	rm -rf *.dSYM
	make clean
	rm -f $(NAME)

re :
	make fclean
	make all
