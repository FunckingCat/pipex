# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unix <unix@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 14:23:43 by unix              #+#    #+#              #
#    Updated: 2021/12/09 16:24:23 by unix             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = gcc -g
FLAGS = 
#FLAGS = -Wall -Werror -Wextra

HEADER = pipex.h

COMMON = ft_error.c ft_validate.c ft_putstr_fd.c ft_split.c
MAIN = pipex.c 
BONUS = 

MAIN_FILES = $(MAIN) $(COMMON)
BONUS_FILES = $(BONUS) $(COMMON)

MAIN_OBJ_FILES = $(MAIN_FILES:.c=.o)
BONUS_OBJ_FILES = $(BONUS_FILES:.c=.o)

RM = rm -f

all: $(NAME)

bonus: $(BONUS_NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(MAIN_OBJ_FILES) $(HEADER)
	$(CC) $(FLAGS) -o $(NAME) $(MAIN_OBJ_FILES) $(LIB)

$(BONUS_NAME): $(BONUS_OBJ_FILES) $(HEADER)
	$(CC) $(FLAGS) -o $(BONUS_NAME) $(BONUS_OBJ_FILES) $(LIB)

clean:
	$(RM) $(MAIN_OBJ_FILES) $(BONUS_OBJ_FILES)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus