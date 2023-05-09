# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: segan <segan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 17:52:39 by segan             #+#    #+#              #
#    Updated: 2023/05/09 18:48:33 by segan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror $(LIBFLAGS)

FWKFLAGS = -framework OpenGl -framework AppKit

HDRFLAGS = -I /usr/local/include

LIBFLAGS = -L /usr/Local/lib/ -lmlx -L ./libft -l ft -L

DEBUG = -g -fsanitize=address

SRCS = main.c errors.c map_validation.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) $(DEBUG) $(CLIBS) -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

clean :
	make -C clean ./libft
	rm -f $(OBJS)

fclean :
	make clean
	make -C fclean ./libft
	rm -rf *.dSYM
	rm -f $(NAME)

re :
	make fclean
	make all
