# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: segan <segan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 17:52:39 by segan             #+#    #+#              #
#    Updated: 2023/05/26 15:26:00 by segan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror

FWKFLAGS = -framework OpenGl -framework AppKit

HDRFLAGS = -I /usr/local/include

LIBFLAGS = -L /usr/Local/lib/ -L ./libft -l ft

DEBUG = -g -fsanitize=address

SRCS = main.c map_validation.c util.c read_map.c\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) $(DEBUG) $(LIBFLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

clean :
	make clean -C ./libft
	rm -f $(OBJS)

fclean :
	make fclean -C ./libft
	rm -rf *.dSYM
	rm -f $(NAME)

re :
	make fclean
	make all
