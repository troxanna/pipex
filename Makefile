# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 19:12:24 by kshanti           #+#    #+#              #
#    Updated: 2021/07/05 19:17:26 by kshanti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

HEAD = ./includes/
SRCS = ./srcs/
GNL = ./gnl/

CFLAGS = -Wall -Wextra -Werror

C_FILE = main.c $(GNL)get_next_line.c $(GNL)get_next_line_utils.c utils.c exec_command.c

O_FILE = $(C_FILE:.c=.o)

all:
	$(MAKE) $(NAME) -j 4

$(NAME): $(O_FILE)
	$(MAKE) -C ./libft bonus
	gcc $(O_FILE) ./libft/libft.a -o $(NAME)

%.o: %.c $(HEAD)
	gcc -c $(СFLAGS) $< -o $@

clean:
	@rm -f $(O_FILE)
	$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
