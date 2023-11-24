# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yallo <yallo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 06:18:38 by yallo             #+#    #+#              #
#    Updated: 2023/11/24 16:16:24 by yallo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
HEADER = philo.h
FLAGS = -Wall -Werror -Wextra -g3 -pthread

SRC_DIR = src/
OBJ_DIR = obj/

SRCS = $(SRC_DIR)main.c $(SRC_DIR)forks.c $(SRC_DIR)init.c \
		$(SRC_DIR)monitoring.c $(SRC_DIR)parse.c \
		$(SRC_DIR)routine.c $(SRC_DIR)threads.c \
		$(SRC_DIR)utils.c
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -O3 -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
