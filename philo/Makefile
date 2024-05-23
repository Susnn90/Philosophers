# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 11:21:46 by cwick             #+#    #+#              #
#    Updated: 2024/05/20 16:40:31 by cwick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c check_input.c create_thread.c init.c utils.c safe_functions.c dinner.c \
	dinner.c getters_setters.c
SRC_OBJ = $(SRC:.c=.o)

CC = cc
DIR = ./philo/
CFLAGS = -Wall -Wextra -Werror -pthread -g

all: $(NAME)

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
