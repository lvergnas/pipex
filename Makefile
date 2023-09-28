# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loura <loura@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 13:49:30 by lvergnas          #+#    #+#              #
#    Updated: 2023/09/27 11:53:38 by loura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= 	gcc
FLAGS	= 	-Wall -Werror -Wextra
RM		= 	rm -rf
NAME	=	pipex
OBJ		=	$(SRC:.c=.o)
SRC		=	pipex.c pipex_utils.c ft_split.c ft_strtrim.c error.c

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