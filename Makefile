# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 18:03:09 by youskim           #+#    #+#              #
#    Updated: 2022/06/27 23:28:06 by youskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Werror -Wall -Wextra 
# -g -fsanitize=address

FILE = main.c \
		make_node.c \
		make_redirect.c \
		change_input.c \
		make_env.c \
		exe_cmd.c \
		do_redirection.c \
		error.c

OBJS = $(FILE:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./libft all
	$(CC) $(OBJS) -lreadline -L./libft -lft -o $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

clean :
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS)

fclean :
	make clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re
