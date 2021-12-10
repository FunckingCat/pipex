# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unix <unix@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 14:23:43 by unix              #+#    #+#              #
#    Updated: 2021/12/10 13:57:05 by unix             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = gcc
FLAGS = 
#FLAGS = -Wall -Werror -Wextra
LIB = -L '.' -lft 

HEADER = pipex.h

MAIN_FILES = pipex.c ft_env.c ft_fork_proc.c ft_exec.c ft_error.c ft_open_in_out.c

MAIN_OBJ_FILES = $(MAIN_FILES:.c=.o)

RM = rm -f

all: $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(MAIN_OBJ_FILES) $(HEADER)
	make bonus -C ./libft
	cp libft/libft.a ./
	$(CC) $(FLAGS) -o $(NAME) $(MAIN_OBJ_FILES) $(LIB)

clean:
	make clean -C ./libft
	$(RM) $(MAIN_OBJ_FILES) $(BONUS_OBJ_FILES)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME) $(BONUS_NAME) libft.a

re: fclean all

.PHONY: all clean fclean re bonus