# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 13:06:22 by anpollan          #+#    #+#              #
#    Updated: 2025/08/06 16:28:26 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRC_DIR		= ./src/
INCL_DIR	= ./incl/
SRC 		= ./src/main.c \
			  ./src/parsing.c \
			  ./src/ft_atoi_safe.c \
			  ./src/free_memory_and_error.c \
			  ./src/routine.c \
			  ./src/routine_utils.c
OBJS 		= $(SRC:%.c=%.o)
HEADER		= ./incl/philo.h
C_FLAGS		= -Wall -Wextra -Werror -pthread -g

all: $(NAME)

$(NAME): $(OBJS)
	cc $(C_FLAGS) $(OBJS) $(MLX) $(MLXFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	cc $(C_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) compile_commands.json

re: fclean all

.PHONY: all clean fclean re
