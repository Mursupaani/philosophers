# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 13:06:22 by anpollan          #+#    #+#              #
#    Updated: 2025/08/14 12:40:12 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRC_DIR		= ./src/
INCL_DIR	= ./incl/
SRC 		= ./src/main.c \
			  ./src/parsing.c \
			  ./src/ft_atoi_safe.c \
			  ./src/free_memory.c \
			  ./src/routine.c \
			  ./src/routine_utils.c \
			  ./src/routine_utils2.c \
			  ./src/initialize.c \
			  ./src/observer_routine.c \
			  ./src/printing.c \
			  ./src/forks.c \
			  ./src/ft_putstr_fd.c \
			  ./src/ft_itoa.c \
			  ./src/error.c
OBJS 		= $(SRC:%.c=%.o)
HEADER		= ./incl/philo.h
C_FLAGS		= -Wall -Wextra -Werror -pthread -g -I$(INCL_DIR)

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

.SECONDARY: $(OBJS)

.PHONY: all clean fclean re
