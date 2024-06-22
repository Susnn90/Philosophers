# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 11:21:46 by cwick             #+#    #+#              #
#    Updated: 2024/06/22 13:54:53 by cwick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c check_input.c threads.c init.c utils.c	actions.c thread_utils.c
SRC_OBJ = $(SRC:.c=.o)

CC = cc
DIR = ./philo/
CFLAGS = -Wall -Wextra -Werror -pthread -g #-fsanitize=thread

all: $(NAME) clean

$(NAME): $(SRC_OBJ)
	$(CC) $(SRC_OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean all
