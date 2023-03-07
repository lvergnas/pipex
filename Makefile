# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 13:49:30 by lvergnas          #+#    #+#              #
#    Updated: 2023/02/27 14:40:10 by lvergnas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= 	gcc
FLAGS	= 	-Wall -Werror -Wextra
RM		= 	rm -rf
NAME	=	pipex
OBJ		=	$(SRC:.c=.o)
SRC		=	pipex.c pipex_utils.c

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) 
		
%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all